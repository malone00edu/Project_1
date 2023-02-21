# Project_1
2023 cs214 project 1 <br>
GROUP ID: 25 <br>
NETID: jn689 & tmb240 SECTION: 06 & 01 <br>

**How malloc works & its implementation:** <br>
This implementation of mymalloc() is a dynamic memory allocation function that allocates a block of memory of the given size. It uses a linked list structure to keep track of free and reserved blocks of memory.

The struct meta has been used to implement a linked list for managing memory allocation and deallocation. It acts as a memory block that holds information such as the size of the block, its reservation status, and pointers to the next and previous blocks. Since metadata plays a crucial role in managing the allocation process, it has a fixed space of 32 bytes within the memory.

mymalloc() checks if the requested size is valid and if the linked list is empty. If the list is empty, it calls allocate_space(). If theres not enough space in memory, "Insufficient space for requested size" error messages will be return. Else, find_space() is called to find a block of memory. If a suitable block is found,it calls allocate_space() and returns the pointer to the data section of the block.

The find_space() helper function goes through the linked list to find the first block of memory that is both free and large enough for the requested size plus the size of a metadata struct. If a block is found, a pointer to its metadata struct is returned. Else, null is returned.

The allocate_space() helper function checks a block of memory and requested size. It marks the block as reserved and returns a pointer to the data section if the size is equal to the requested size. If the size is less, it returns NULL. If the size is more, it creates a new block, updates the metadata, links it to the list, and returns a pointer to the data section.

**How free works & its implementation:**

myfree() deallocates the memory associated with the given pointer, updates the header information, and coalesces adjacent free blocks (eager approach) to avoid memory fragmentation. 

The myfree() implementation first checks if the ptr passed to it is a null pointer, if it is,  prints an error message and returns. The find_ptr() function to check if the given pointer exists within the linked list. If its not within the scope, "Pointer does not exist within the heap/linked list", will be return. If the ptr is not null, it assumes that it was previously allocated using mymalloc(), thus, there should be a struct meta header associated with it. It retrieves the header by subtracting the size of struct meta from the ptr.

If the boolean "reserved" is false, that means the the memory is already freed or invalid so it prints an error message and returns (double free detected). If the reserved is true, it sets the value to false, thus the memory is now freed.

myfree() checks if the previous or next memory block is free, and if so, it coalesces the blocks. If the previous block is free, myfree() combines the current block with the previous block, updating the size of the combined block and the pointers. If the next block is free, myfree() combines the current block with the next block.


**Instructions for MakeFile**<br>
Navigate to the directory where this assignment is stored using the terminal on a Linux device, and then type "make" in the same folder. The purpose of this is to make sure the program compiles properly.

**Testing** /*All scenarios mention here are tested in memgrind.c*/

**Testing if malloc and free works:** <br>
To check if malloc and free are functioning properly, we initalize three pointers, and allocate memory for each of them using malloc(). We can conclude that malloc is working correctly by printing the addresses and verifying that they are distinct. <br>
Similarly, to test free, we can free all three ptrs, create a new pointer (to keep things controlled) and call malloc(). If the new pointer has the same address as the first ptr, we can confirm that free is working as intended.

**Errors:**
There are several error messages that can be returned, along with the filename and line where they occurred:
1. "Insufficient space for requested size": This error occurs when attempting to allocate memory with malloc() and there isn't enough space in memory to satisfy the request.
2. "Cannot free a null pointer": This error occurs when trying to free a pointer that is null.
3. "Pointer does not exist within the heap/linked list": This error occurs when trying to free an address that hasn't been allocated by malloc(), or an address that isn't at the start of the allocated memory block.
4. "Double free detected": This error occurs when trying to free an address that has already been freed.


**Testing for memory fragmentation:** 
1. Three pointers are initialized with different sizes.
2. Pointers 1 and 2 are freed to create a block of memory.
3. Pointer 3 is freed to check if the blocks are properly coalesced.
4. Pointer 4 is then initialized and its address is compared with that of pointer 1. If they have the same address, it indicates that the blocks have been successfully coalesced.


**Performance testing:**<br>
Each task is run 50 times and the average time is printed. A lower average time indicates that the program is faster and more efficient.

**/*test1*/** <br>involves using the malloc() function to allocate a 1-byte chunk of memory and immediately using the free() function to deallocate it. This is repeated 120 times and is implemented using a simple for loop.


**/*test2*/** <br> involves using the malloc() function to allocate 120 1-byte chunks of memory and storing the pointers in an array. It then uses the free() function to deallocate the chunks by iterating through the array with another for loop.

**/*test3*/** <br>randomly alternates between allocating and deallocating 1-byte chunks of memory until 120 malloc calls have been made. After the loop is complete, it frees any remaining allocated memory.

Implementation:
1. Declare an array of 120 pointers myPtrs and an array of 120 integers mallocPtrTracker. Initialize all elements of mallocPtrTracker to -1.
2. Declare variables to keep track of the number of malloc calls numOfMallocCalls, the current position in the myPtrs array count, the limit of the array limit, and a random number randNum.
3. Start a while loop that will continue until 120 malloc calls have been made. At each iteration, generate a random number randNum that is either 1 or 2.
4. If randNum is 2, allocate a 1-byte chunk of memory using malloc and store the pointer in the myPtrs array at position count. Increment numOfMallocCalls, set the corresponding element in mallocPtrTracker to 1 to indicate that the pointer has been allocated, and increment count. If count is greater than limit, update limit to be count.
5. If randNum is 1, free the pointer stored in the myPtrs array at position count-1. Decrement count and set the corresponding element in mallocPtrTracker to 0 to indicate that the pointer has been freed.
6. After the while loop has finished, iterate through the myPtrs array up to the limit position. For each pointer that has been allocated (indicated by mallocPtrTracker being 1), free the memory.

**/*test4*/** <br>
Malloc or free randomizer. Malloc two different sizes. 1 or 2 will malloc their respective sizes. 3 will free a previous malloc. The size of the memory allocated is either 5 bytes or 10 bytes. It stores the pointers to the allocated memory in an array called myPtrs and tracks whether the memory at a particular position in the array has been allocated or freed using the ptrStatusTracker array. The program continues to allocate and free memory until it has done so 120 times. Once this loop is finished, the program checks each element in myPtrs to ensure that all memory that was allocated has been freed, freeing any memory that was not previously freed.(implementation is similar to test3 but with more conditions)

**/*test5*/** <br>
Malloc an ever-increasing sum until it triggers an insufficient space error. Free all malloc pointers within the array. Starting with the first (lower) index, then immediately free the last (upper) index. Increase lower by 1. Decrease upper by 1. Repeat until all pointers are freed.
