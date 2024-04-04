#include <stdio.h> 
#include <omp.h>

int main(){
    int i, j, k; 
    int m = 5, n = 5 , p = 2;
    int A[m][n], B[n][p], C[m][p];

    // Assigning value
    for (i = 0; i<m; i++){
        for (j = 0; j<n; j++){
            A[i][j] = i+j;
        }
    }

    for (i = 0; i<n; i++){
        for (j = 0; j<p; j++){
            B[i][j] = i*j;
        }
    }

    // Paralle segment by row
    omp_set_num_threads(2);
    int threadID, start, end;
    #pragma omp parallel private(threadID, start, end,  i, j, k)
    {
        int NT = omp_get_num_threads();
        int Ms = m/NT;
        threadID = omp_get_thread_num(); // divide threads then solve at each level of for-s
        start = threadID*Ms; 
        end = start+Ms; 
        if (end < m && threadID == NT-1){
            end = m;
        }
        for (i=start; i < end; i++){
            for (k = 0; k < p; k++){
                C[i][k] = 0;
                for (j = 0; j < n; j++){
                    C[i][k] += A[i][j] * B[j][k];
                }
            }
        }

    }

    // Older style
    // for (i = 0; i<m; i++){
    //     for (k = 0; k<p; k++){
    //         C[i][k] = 0;
    //         for (j = 0; j<n; j++){
    //             C[i][k] += A[i][j]*B[j][k];
    //         }
    //     }
    // }

    // Print results
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (i = 0; i < n; i++) {
        for (j = 0; j < p; j++) {
            printf("%d ", B[i][j]);
        }
        printf("\n");
    }

    printf("\n");

    for (i = 0; i < m; i++) {
        for (j = 0; j < p; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }

    return 0;
}