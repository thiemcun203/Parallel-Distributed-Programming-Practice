#include <mpi.h>
#include <stdio.h>
#include <malloc.h>
int main(int argc, char *argv[]) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int Nr_of_Process, ID_of_Process;
    MPI_Comm_size(MPI_COMM_WORLD, &Nr_of_Process);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &ID_of_Process);

    MPI_Status status;


    int i;
    if (ID_of_Process == 0){
        int *A;
        A = (int *)malloc(10 * sizeof(int));
        for (i = 0; i < 10; i++){
            *(A+i) = i;
        }
        MPI_Send(A, 10,MPI_INT, 1,2024, MPI_COMM_WORLD);
        printf("At processor: %d\n", ID_of_Process);
        for (i = 0; i < 10; i++){
            printf("%d\n", *(A+i));
        }
    } else{
        int *B, *C;
        B = (int *)malloc(10*sizeof(int)); // so phan tu gui du ra, se bi treo, do doi nhan (sync)
        C = (int *)malloc(10*sizeof(int)); // so phan tu nhan duoc, se bi treo
        MPI_Recv(B, 10, MPI_INT, 0, 2024, MPI_COMM_WORLD, &status);
        for (i = 0; i < 10; i++){
            *(C+i) = *(B+i) * 2;
        }
        printf("At processor: %d\n", ID_of_Process);
        for (i = 0; i < 10; i++){
            printf("%d\n", *(C+i));
        }


    }

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
