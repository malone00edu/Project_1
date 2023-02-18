# Project_1
2023 cs214 project 1

**How malloc works & its implementation:** <br>
This implementation of mymalloc() is a dynamic memory allocation function that allocates a block of memory of the given size. It uses a linked list structure to keep track of free and reserved blocks of memory.

The find_space() helper function goes through the linked list to find the first block of memory that is both free and large enough for the requested size plus the size of a metadata struct. If a block is found, a pointer to its metadata struct is returned. If not, NULL is returned.

The allocate_space() helper function takes a pointer to a block of memory and the requested size as arguments. It marks the block as reserved and returns a pointer to the data section if the size is equal to the requested size. If the size is less, it returns NULL. If the size is more, it creates a new block, updates the metadata, links it to the list, and returns a pointer to the data section.

mymalloc() checks if the requested size is valid and if the linked list is empty. If the list is empty, it calls allocate_space(). If there's not enough memory, it prints an error message and returns NULL. If the list isn't empty, it calls find_space() to find a block of memory. If it's found, it calls allocate_space() and returns the pointer to the data section of the allocated memory.

**How free works & its implementation:**

myfree() deallocates the memory associated with the given pointer, updates the header information, and coalesces adjacent free blocks (eager approach) to avoid memory fragmentation. 

The myfree() implementation first checks if the ptr passed to it is a null pointer, if it is,  prints an error message and returns. It calls the find_ptr() function to check if the given pointer exists within the scope of the heap/linked list. If it doesn't, it prints an error message and returns. If the ptr is not null, it assumes that it was previously allocated using mymalloc(), thus, there should be a struct meta header associated with it. It retrieves the header by subtracting the size of struct meta from the ptr.

If the boolean "reserved" is false, that means the the memory is already freed or invalid so it prints an error message and returns (double free detected). If the memory is valid, reserved is true, it sets the value to false, thus the memory is now freed.

Next, the function checks if the previous or next memory block is free, and if so, it coalesces the blocks. If the previous block is free, myfree() combines the current block with the previous block, updating the size of the combined block and the pointers. If the next block is free, myfree() combines the current block with the next block.


**Testing** /*All scenarios mention here are tested in memgrind.c*/

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


**Performance testing:**

//tests malloc and free<br /> 
test1: Use malloc() and immediately free() a 1-byte chunk, 120 times.
<br /> 
-Using a for loop to allocate & deallocate memory 120 times. 
<br /> 
-prints out address of initial and final address, if initial address is the same 
 as final that means malloc and free is working as intended

<br /> 
test2: Use malloc() to get 120 1-byte chunks, storing the pointers in an array, then use free() to
deallocate the chunks.
<br /> 
-Same as test one but using an array to store the pointers.
<br /> 
-Prints out couple addresses to show that each address should be different by one byte.

