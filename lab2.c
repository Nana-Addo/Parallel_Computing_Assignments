#include<stdio.h>
#include<mpi.h>

int main(int argc, char ** argv)
{ 
    int mynode, totalnodes; int sum,startval,endval,accum;
    double t1, t2;
    MPI_Status status;
    MPI_Init(&argc,&argv);
    MPI_Comm_size(MPI_COMM_WORLD, &totalnodes);
    MPI_Comm_rank(MPI_COMM_WORLD, &mynode);

    MPI_Barrier(MPI_COMM_WORLD);
    t1 = MPI_Wtime();
    sum = 0;
    startval = 1000*mynode/totalnodes+1;
    endval = 1000*(mynode+1)/totalnodes;

    for (int i = startval; i <= endval; i = i + 1)
            sum = sum + i;

    if (mynode!=0)
        MPI_Send(&sum,1,MPI_INT,0,1,MPI_COMM_WORLD);
    else
        for(int j=1;j<totalnodes;j=j+1)
    {
        MPI_Recv(&accum,1,MPI_INT,j,1,MPI_COMM_WORLD,
        &status);
        sum = sum + accum;
    }

    MPI_Barrier(MPI_COMM_WORLD);
    t2 = MPI_Wtime();
    if(mynode == 0)
    { 
        printf("The sum from 1 to 1000 is: %d\n", sum );
        printf("Output: On %i Nodes\n", totalnodes);
        printf("Execution Time: %f\n", (t2 - t1));
    }
    MPI_Finalize();
}