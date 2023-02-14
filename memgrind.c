#include <stdio.h>
#include "mymalloc.h"

int *myPtrs[1000]; //Store malloc pointers. Arbitrary number chosen for array.

//testing malloc
void test1(){
    int i;
    char *pointers[10];
    
    //allocating 10 blocks of size 10
    printf("\n1: Testing Malloc\n");
    for (i = 0; i < 10; i++){
        pointers[i] = (char*)malloc(10);
        printf("%d: %p\n", i, pointers[i]);
    }

}

//testing if free work properly, if using malloc uses same space as previous testcase then that mean it works!
void test2(){
    int i;
    char *pointers[10];
    
    printf("\n2: Testing free\n");

    printf("BEFORE FREE: \n");
    for (i = 0; i < 10; i++){
        printf("%d: %p\n", i, pointers[i]);
    }
    
    //freeing previous pointers
    for (i=0; i<10; i++){
        free(pointers[i]);
    }
    
     printf("\nAFTER FREE AND ALLOCATING: \n");
    //allocating 10 blocks of size 10
    for (i = 0; i < 10; i++){
        pointers[i] = (char*)malloc(10);
        printf("%d: %p\n", i, pointers[i]);
    }
    
 

}

void test3() {
    printf("\n3: Testing for coalesce\n");

    int *ptr1 = (int*)malloc(3 * sizeof(int));
    int *ptr2 = (int*)malloc(2 * sizeof(int));
    int *ptr3 = (int*)malloc(2 * sizeof(int));
    printf("Ptr1: %p\n", ptr1);
    printf("Ptr2: %p\n", ptr2);
    printf("Ptr3: %p\n", ptr3);

    // Free ptr1 and ptr2 to create two separate blocks
    free(ptr1);
    free(ptr2);

    // Call free on ptr3 to see if the free blocks are coalesced
    free(ptr3);

    // Verify that the free blocks have been coalesced
    // by checking the memory addresses
    int *ptr4 = (int*)malloc(5 * sizeof(int));
    printf("Ptr4: %p\n", ptr4);
    
    
    /*If it is equal, that means the three separate free blocks have been
    coalesced into one large block and ptr4 is using the memory from this large block.*/
    if (ptr4 == ptr1) {
        printf("Coalescing successful!\n");
    } else {
        printf("Coalescing unsuccessful.\n");
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

    
    //test if malloc works
    test1();
    
    //testing if free works
    test2();
    
    //test for Coalescing
    test3();
    
    return 0;
}
