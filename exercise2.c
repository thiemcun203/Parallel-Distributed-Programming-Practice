#include <stdio.h>
#include <omp.h>
int main(){
    
    int id, x;
    omp_set_num_threads(100);
    #pragma omp parallel private(id,x)
    {
        
        id = omp_get_thread_num();
        x = 10*id;
        printf("\n"); // -> this make delay
        printf("Thread ID: %d, x = %d\n", id, x);
        printf("\n");
    }
}

// wrong -> many duplicates cw, cr, ew, ex -> race condition
// it like when 100 thread run, thread 62 write to x = 620, id = 62, but some thread print delay
// we can use private(id,x) avoid race condition id, x, but it occupy alot memory increase n (threads) times x
// if we create virtual thread, it still appear deadlock
// should not declear inside, local domain