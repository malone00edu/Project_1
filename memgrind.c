#include <stdio.h>
#include "mymalloc.h"

int *myPtrs[1000]; //Store malloc pointers. Arbitrary number chosen for array.

//malloc() and immediately free() a 1-byte chunk, 120 times.
void test1(){
    int i;
    printf("\nTest1\n");
    for (i = 0; i < 120; i++) {
        char *ptr = (char *) malloc(1);
        //prints out address of initial and final address, if initial address is the same 
        //as final that means malloc and free is working as intended
        if (i==0 || i==119){
            printf("%d: %p\n",i, ptr);
        }
        free(ptr);
    }
    
}

void test2(){
    void *arr[120];
    int i;

    // Allocate 120 1-byte chunks and store pointers in array
    printf("\nTest2\n");;
    for (i = 0; i < 120; i++) {
        arr[i] = malloc(1);
        if (i==0 || i==1 || i==119){
            printf("%d: %p\n",i, arr[i]);
        }
    }

    //Dellocating all chunks
    for (i = 0; i < 120; i++) {
        free(arr[i]);
    }
    
}

void testcoalesce() {
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
    
    test1();
    test2();
    
 
    return 0;
}
