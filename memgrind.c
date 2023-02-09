#include <stdio.h>
#include "mymalloc.h"

int *myPtrs[1000]; //Store malloc pointers. Arbitrary number chosen for array.



int main() {
    // Testing malloc implementation.
    for(int i = 0; i < 1; i++){
        myPtrs[i] = (int *) malloc(4968);
    }
    for(int i = 0; i < 10; i++){
        printf("%d: %p\n", i, myPtrs[i]);
    }
    
    //Testing free implementation.
    for (int i = 0; i < 1; i++) {
        free(myPtrs[i]);
    }
    
    for(int i = 0; i < 10; i++){
        printf("%d: %p\n", i, myPtrs[i]);
    }
    return 0;
}
