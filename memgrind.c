#include <stdio.h>
#include "mymalloc.h"

int *myPtrs[1000]; //Store malloc pointers. Arbitrary number chosen for array.

//testing malloc
void test1(){
    int i;
    char *pointers[10];
    
    //allocating 10 blocks of size 10
    printf("Test 1:\n");
    for (i = 0; i < 10; i++){
        pointers[i] = (char*)malloc(10);
        printf("%d: %p\n", i, pointers[i]);
    }

}

//testing if free work properly, if using malloc uses same space as previous testcase then that mean it works!
void test2(){
    int i;
    char *pointers[10];

    printf("Test 2:\n");
    //freeing previous pointers
    for (i=0; i<10; i++){
        free(pointers[i]);
    }
    
    //allocating 10 blocks of size 10
    for (i = 0; i < 10; i++){
        pointers[i] = (char*)malloc(10);
        printf("%d: %p\n", i, pointers[i]);
    }
   
}


int main() {
    // Testing malloc implementation.

    for(int i = 0; i < 1; i++){
        myPtrs[i] = (int *) malloc(500);
    }
    for(int i = 0; i < 10; i++){
        printf("%d: %p\n", i, myPtrs[i]);
    }


    test1();
    test2();
    
    return 0;
}
