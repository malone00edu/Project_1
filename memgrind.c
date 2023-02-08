#include <stdio.h>
#include "mymalloc.h"

int *myPtrs[1000]; //Store malloc pointers. Arbitrary number chosen for array.

int main() {
    // Testing malloc implementation.
    for(int i = 0; i < 9; i++){ // Allocate 500 bytes ten times. (Fills up memory completely)
        myPtrs[i] = (int *) malloc(500);
        printf("%d: %p\n", i, myPtrs[i]);
    }
    return 0;
}