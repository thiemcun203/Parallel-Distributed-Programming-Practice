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
    omp_set_num_threads(n);
    int threadID;
    #pragma omp parallel private(threadID, i)
    {
        threadID = omp_get_thread_num();
        for (i = 0; i<p; i++){
            C[threadID][i] = 0;
            for (j = 0; j < n; j++){
                C[threadID][i] += A[threadID][j] * B[j][i];
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