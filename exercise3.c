#include <stdio.h>
#include <omp.h>

int main(){
    int i, N=20;
    int A[N], B[N], C[N];
    for (i=0; i<N; i++){
        A[i] = i; B[i] = 2*i;
    }
    omp_set_num_threads(5);
    int threadID;
    #pragma omp parallel private(threadID, i) // if we use private(thread), we must declare threadID before using
    // for (i = 0; i<N; i++){
    //     C[i] = A[i]+B[i];
    // }
    {
        int NT = omp_get_num_threads();
        Ns = N/NT;
        threadID = omp_get_thread_num();
        start = threadID*Ns;
        end = start+Ns;

        // each thread, core solve Ns elements
        for (i = start; i<end; i++){    
            C[i] = A[i]+B[i];   
        }


        // C[threadID] = A[threadID] + B[threadID];
    }

    for (i = 0; i<N; i++){
        printf("%d\n",A[i]); 
    }
    for (i= 0; i<N; i++){
        printf("%d\n",B[i]);
    }
    for (i = 0; i<N; i++){
        printf("%d\n",C[i]); 
    }


}