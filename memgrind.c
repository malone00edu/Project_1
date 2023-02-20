#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "mymalloc.h"


/*
 * Malloc() and immediately free() a 1-byte chunk, 120 times.
 */
void test1(){

    int i;
    for (i = 0; i < 120; i++) {
        char *ptr = (char *) malloc(1);
        free(ptr);
    }

}
/*
 * First allocate 120 1-byte chunks and store the pointers in an array.
 * Then free all allocated chunks within the heap using the stored pointers.
 */
void test2(){

    void *arr[120];
    int i;

    // Allocate 120 1-byte chunks and store pointers in array
    for (i = 0; i < 120; i++) {
        arr[i] = malloc(1);
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

    char *myPtrs[120];
    int ptrStatusTracker[120];
    for(int i = 0; i < 120; i++){ // Replace garbage numbers stored in the array with -1
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
        //printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
        if(ptrStatusTracker[i] != 0){ // Free any pointers that was not freed within the while loop.
            free(myPtrs[i]);
            ptrStatusTracker[i] = 0;
        }
    }
    /*printf("\n-----------------------\n");
    for (int i = 0; i < limit; i++) { // Print all freed positions.
            printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
    }*/
}

/*
 * Malloc or free randomizer. Malloc two different sizes. 1 or 2 will malloc their respective sizes.
 * 3 will free a previous malloc.
 */
void test4(){

    char *myPtrs[120];
    int ptrStatusTracker[120];
    for(int i = 0; i < 120; i++){ // Replace garbage numbers stored in the array with -1
        ptrStatusTracker[i] = -1;
    }
    int numOfMallocCalls = 0;
    int count = 0;
    int limit = 1;
    int randNum;
    while(numOfMallocCalls < 120){
        randNum = rand() % 5 + 1; // Outputs 1 to 5 randomly.
        //printf("Random num: %d\n", randNum);
        if(randNum == 1){ // Malloc the current count position if ranNum = 1
            myPtrs[count] = malloc(5);
            numOfMallocCalls++; //When this number hits 120. Exit the while loop.
            ptrStatusTracker[count] = 1; //This position was last marked as malloc.
            count++;
            if(count > limit){
                limit = count;
            }
        }
        else if(randNum == 2){ // Malloc the current count position if randNum = 2
            myPtrs[count] = malloc(10);
            numOfMallocCalls++; //When this number hits 120. Exit the while loop.
            ptrStatusTracker[count] = 2; //This position was last marked as malloc.
            count++;
            if(count > limit){
                limit = count;
            }
        }
        else{ // Else free the last malloc position if randNum = 3, 4 or 5
            if (count > 1) {
                count--;
                free(myPtrs[count]);
                ptrStatusTracker[count] = 0; // This position was last marked as freed.
            }
        }
    }
    for (int i = 0; i < limit; i++){
        //printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
        if(ptrStatusTracker[i] != 0){ // Free any pointers that was not freed within the while loop.
            free(myPtrs[i]);
            ptrStatusTracker[i] = 0;

        }
    }
    /*printf("\n-----------------------\n");
    for (int i = 0; i < limit; i++){ // Print all freed positions.
        if(ptrStatusTracker[i] == 0) {
            printf("%d: Last marked status: %d\n", i, ptrStatusTracker[i]);
        }
    }*/
}

/*
 * Malloc an ever-increasing sum until it triggers an insufficient space error. Free all malloc pointers within
 * the array. Starting with the first (lower) index, then immediately free the last (upper) index. Increase lower
 * by 1. Decrease upper by 1. Repeat until all pointers are freed.
 */
void test5(){

    char *myPtrs[5000];
    struct meta *ptr = malloc(1);
    int num = 1;
    int sum = 0;
    int index = 0;
    while(ptr){
        sum = sum + num;
        ptr = malloc(sum); // When requested malloc sum triggers an insufficient space error, exit the while loop.
        //printf("Sum is %d: \n", sum);
        if(ptr == NULL){
            break;
        }
        fclose(stderr); // Comment fclose out to see verification of insufficient space error.
        myPtrs[index] = (char *) ptr;
        index++;
        num++;
    }

    int lower = 0;
    int upper = index - 1;
    while(lower < upper){ // Free the 1st malloc sum of the array. Then free the last malloc sum of the array.
        if(lower == upper){ // Free the middle index and exit loop.
            free(myPtrs[lower]);
            break;
        }
        free(myPtrs[lower]);
        free(myPtrs[upper]);
        lower++; // Move on to the next malloc sum. From left to right.
        upper--; // Move on to the previous malloc sum. From right to left.
    }
}

/*
 * Test to see if the heap is correctly coalescing different sizes of byte chunks.
 */
void testcoalesce() {
    printf("\nTesting for coalesce:\n");

    int *ptr1 = malloc(3);
    int *ptr2 = malloc(2);
    int *ptr3 = malloc(2);
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
    int *ptr4 = (int*)malloc(5);
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

//Testing if malloc and free works properly
void testMallocFree() {

    printf("\nTesting malloc and free: \n");
    char *ptr[3];
    //test malloc
    for (int i=0 ;i<3; i++){
        ptr[i] =  malloc(10);
        printf("%d: %p \n", i, ptr[i]);
    }

    //test free
    for (int i=0 ;i<3; i++){
        free(ptr[i]);
    }
    //initialize a new ptr and call malloc
    //checks if newptr address is the same as the first ptr, if it's the same then free works.
    char *newptr = malloc(20);
    printf("newptr is at address: %p\n",newptr);
    free(newptr);
    printf("\n");


}




/*
 * Main is used to test error detection along with a variety of heap stress tests.
 */
int main() {
    /*Testing malloc and free*/
    testMallocFree();

    /*Testing Errors*/

    printf("Testing various errors:\n");
    //Calling free with a NULL pointer.
    struct meta *nPtr = NULL;
    free(nPtr);

    //Testing what happens when you overfill memory.
    struct meta *mPtr= malloc(5000);
    free(mPtr);

    //Free an address that is not obtain from using malloc()
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
    printf("\nStress Tests:");

    struct timeval beginning, end;
    double total;
    double average;
    int laps;


    printf("\nTest1\n");
    total = 0;
    for(laps = 0; laps < 50; laps++){
        gettimeofday(&beginning, NULL);
        test1();
        gettimeofday(&end, NULL);
        total += (end.tv_sec - beginning.tv_sec) * 1e6;
        total += (total + (end.tv_usec - beginning.tv_usec)) * 1e-6;
    }
    average = total / 50;
    printf("Average runtime of %d laps = %1.9f sec\n", laps, average);


    printf("\nTest2\n");
    total = 0;
    for(laps = 0; laps < 50; laps++){
        gettimeofday(&beginning, NULL);
        test2();
        gettimeofday(&end, NULL);
        total += (end.tv_sec - beginning.tv_sec) * 1e6;
        total += (total + (end.tv_usec - beginning.tv_usec)) * 1e-6;
    }
    average = total / 50;
    printf("Average runtime of %d laps = %1.9f sec\n", laps, average);


    printf("\nTest3\n");
    total = 0;
    for(laps = 0; laps < 50; laps++){
        gettimeofday(&beginning, NULL);
        srand(time(NULL));
        test3();
        gettimeofday(&end, NULL);
        total += (end.tv_sec - beginning.tv_sec) * 1e6;
        total += (total + (end.tv_usec - beginning.tv_usec)) * 1e-6;
    }
    average = total / 50;
    printf("Average runtime of %d laps = %1.9f sec\n", laps, average);


    printf("\nTest4\n");
    total = 0;
    for(laps = 0; laps < 50; laps++){
        gettimeofday(&beginning, NULL);
        srand(time(NULL));
        test4();
        gettimeofday(&end, NULL);
        total += (end.tv_sec - beginning.tv_sec) * 1e6;
        total += (total + (end.tv_usec - beginning.tv_usec)) * 1e-6;
    }
    average = total / 50;
    printf("Average runtime of %d laps = %1.9f sec\n", laps, average);


    printf("\nTest5\n");
    total = 0;
    for(laps = 0; laps < 50; laps++){
        gettimeofday(&beginning, NULL);
        test5();
        gettimeofday(&end, NULL);
        total += (end.tv_sec - beginning.tv_sec) * 1e6;
        total += (total + (end.tv_usec - beginning.tv_usec)) * 1e-6;
    }
    average = total / 50;
    printf("Average runtime of %d laps = %1.9f sec\n", laps, average);

    return 0;
}
