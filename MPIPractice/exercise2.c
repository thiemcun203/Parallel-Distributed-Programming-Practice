#include <mpi.h>
#include <stdio.h>
#include <malloc.h>

int main(int argc, char *argv[]) {
    int np, RANK;
    int N = 10;

    // Initialize the MPI environment
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &np);
    MPI_Comm_rank(MPI_COMM_WORLD, &RANK);
    MPI_Status Warning;

    int i,p;
    int *A,*B,*C; 
    A = (int *) malloc (N*sizeof(int));
    B = (int *) malloc (N*sizeof(int));
    C = (int *) malloc (N*sizeof(int));
    // Innitialize Input Data
    if (RANK == 0){
        for (i = 0; i < 10; i++){
            *(A+i) = i;
            *(B+i) = 2*i;
        }
    }

    //1. Domain Decomposition
    int Ns = N/np;
    int *As, *Bs, *Cs;
    As = (int *)malloc(Ns * sizeof(int));
    Bs = (int *)malloc(Ns * sizeof(int));
    Cs = (int *)malloc(Ns * sizeof(int));

    // 2. Distribut input data
    if (RANK == 0){
        // Assign first subdomain for rank 0
        for (i = 0; i < Ns; i++){
            *(As+i) = *(A+i);
            *(Bs+i) = *(B+i);
        }
        // Send each part of A and B to correct other rank
        for (int p = 1; p<np; p++){
            MPI_Send(A+p*Ns, Ns, MPI_INT, p, p, MPI_COMM_WORLD); // must different tag in A, B send
            MPI_Send(B+p*Ns, Ns, MPI_INT, p, 1000+p, MPI_COMM_WORLD);
        }

    } else{
        // Receive correct part of A and B from rank 0
        MPI_Recv(As, Ns, MPI_INT, 0, RANK, MPI_COMM_WORLD, &Warning);
        MPI_Recv(Bs, Ns, MPI_INT, 0, 1000+RANK, MPI_COMM_WORLD, &Warning);
    }
    
    // 3. Exchange data IF require
    // Dont need exchange data because of independency

    // 4. Computation
    for (i = 0; i < Ns; i++){
        *(Cs+i) = *(As+i) + *(Bs+i);
    }

    //5. Gather output, is inverted of distribute input
    if (RANK != 0){
        // Send to rank 0
        MPI_Send(Cs, Ns, MPI_INT, 0, 2000+RANK, MPI_COMM_WORLD);
    } else{
       // Assign first domain
       for (i = 0; i < Ns; i++){
           *(C+i) = *(Cs+i);
       }
       // Receive subdomain from other rank and store corectly
       for (int p = 1; p < np; p++){
           MPI_Recv(C+p*Ns, Ns, MPI_INT, p, 2000+p, MPI_COMM_WORLD, &Warning);
       }
       for (i=0;i<N;i++) printf("%d ", *(C+i));
    }

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
