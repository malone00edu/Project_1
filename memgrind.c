#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

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
/*
 * Malloc or free randomizer. Malloc one size. 1 will malloc it's respective size. 2 will free a previous malloc.
 */
void test3(){
    printf("\nTest3\n");;
    char *myPtrs[120];
    int ptrStatusTracker[120];
    for(int i = 0; i < 120; i++){
        ptrStatusTracker[i] = -1;
    }
    int numOfMallocCalls = 0;
    int count = 0;
    int limit = 1;
    int randNum;
    while(numOfMallocCalls < 120){
        randNum = rand() % 2 + 1; // Outputs 1 or 2 randomly.
        if(randNum == 1){ // Malloc the current count position if ranNum = 1
            myPtrs[count] = malloc(1);
            numOfMallocCalls++; //When this number hits 120. Exit the while loop.
            ptrStatusTracker[count] = 1; //This position was last marked as malloc.
            count++;
            if(count > limit){
                limit = count;
                //printf("New limit: %d\n", limit);
            }
        }
        else{ // Free the last malloc position if ranNum = 2
            if (count > 1) {
                count--;
                free(myPtrs[count]);
                ptrStatusTracker[count] = 0; // This position was last marked as freed.
            }
        }
    }
    for (int i = 0; i < limit; i++){
        if(ptrStatusTracker[i] != 0){ // Free any pointers that was not freed within the while loop.
            printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
            free(myPtrs[i]);
            ptrStatusTracker[i] = 0;
        }
    }
    printf("\n-----------------------\n");
    for (int i = 0; i < limit; i++) { // Print all freed positions.
            printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
    }
}
/*
 * Malloc or free randomizer. Malloc two different sizes. 1 or 2 will malloc their respective sizes.
 * 3 will free a previous malloc.
 */
void test4(){
    printf("\nTest4\n");;
    char *myPtrs[120];
    int ptrStatusTracker[120];
    for(int i = 0; i < 120; i++){
        ptrStatusTracker[i] = -1;
    }
    int numOfMallocCalls = 0;
    int count = 0;
    int limit = 1;
    int randNum;
    while(numOfMallocCalls < 120){
        randNum = rand() % 3 + 1; // Outputs 1 to 3 randomly.
        //printf("Random num: %d\n", randNum);
        if(randNum == 1){ // Malloc the current count position if ranNum = 1
            myPtrs[count] = malloc(10);
            numOfMallocCalls++; //When this number hits 120. Exit the while loop.
            ptrStatusTracker[count] = 1; //This position was last marked as malloc.
            count++;
            if(count > limit){
                limit = count;
                //printf("New limit: %d\n", limit);
            }
        }
        else if(randNum == 2){ // Malloc the current count position if randNum = 2
            myPtrs[count] = malloc(20);
            numOfMallocCalls++; //When this number hits 120. Exit the while loop.
            ptrStatusTracker[count] = 2; //This position was last marked as malloc.
            count++;
            if(count > limit){
                limit = count;
                //printf("New limit: %d\n", limit);
            }
        }
        else{ // Else free the last malloc position if randNum = 3
            if (count > 1) {
                count--;
                free(myPtrs[count]);
                ptrStatusTracker[count] = 0; // This position was last marked as freed.
            }
        }
    }
    for (int i = 0; i < limit; i++){
        printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
        if(ptrStatusTracker[i] != 0){ // Free any pointers that was not freed within the while loop.
            free(myPtrs[i]);
            ptrStatusTracker[i] = 0;

        }
    }
    printf("\n-----------------------\n");
    for (int i = 0; i < limit; i++){ // Print all freed positions.
        if(ptrStatusTracker[i] == 0) {
            printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
        }
    }
}

void testcoalesce() {
    printf("\nTesting for coalesce\n");

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
    
    free(ptr4);
}


int main() {
    /*Testing Errors*/
    //testing what happens when you overfill memory.
    int *m = malloc(sizeof(int)*5000);
    
    //free an address that is not obtain from using malloc()
    int x;
    free(&x);
    
    //Calling free() with an address not at the start of a chunk.
    int *p = malloc(sizeof(int)*2);
    free(p + 1);
    
    //Calling free() a second time on the same pointer. 
    int *q = p;
    free(p);
    free(q);
    
    //Testing for memory fragmentation
    testcoalesce();
    
    /*Stress test*/
    printf("\nStress Test");
    test1();
    test2();
    srand(time(NULL));
    test3();
    srand(time(NULL));
    test4();
    
    
  
    
    

    
    
 
    return 0;
}
