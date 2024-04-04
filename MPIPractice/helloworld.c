#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int Nr_of_Process, ID_of_Process;
    MPI_Comm_size(MPI_COMM_WORLD, &Nr_of_Process);

    // Get the rank of the process
    MPI_Comm_rank(MPI_COMM_WORLD, &ID_of_Process);

    // Print a hello world message
    printf("Hi from rank %d in total %d processors\n", ID_of_Process, Nr_of_Process);

    // Finalize the MPI environment.
    MPI_Finalize();

    return 0;
}
