#include <stdio.h>
#include <mpi.h>

int main (int argc, char **argv){
    int id, np, dato = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_COMM_size(MPI_COMM_WORLD, &np);

    if(id == 0){
        dato = 5;
    }

    MPI_Bcast(&dato, 1, MPI_INT, 0, MPI_COMM_WORLD);
    printf("Dato de proceso %d es %d", id, dato);

    MPI_Finalize();
return 0;
}