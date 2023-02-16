# Project_1
2023 cs214 project 1

How malloc works & its implementation:


How free works & its implementation:

In short, free() frees the memory associated with the given pointer, updates the header information, and coalesces adjacent free blocks (eager approach)to avoid memory fragmentation. 

The myfree() implementation first checks if the ptr passed to it is a null pointer, if it is,  prints an error message and returns. If the ptr is not null, it assumes that it was previously allocated using mymalloc(), thus, there should be a struct meta header associated with it. It retrieves the header by subtracting the size of struct meta from the ptr.

If the reserved is already false, that means the the memory is already freed or invalid, so it prints an error message and returns. If the memory is valid and reserved, it sets the reserved to false, thus the memory is now freed.

Next, the function checks if the previous or next memory block is free, and if so, it coalesces the blocks. If the previous block is free, myfree() combines the current block with the previous block, updating the size of the combined block and the pointers. If the next block is free, myfree() combines the current block with the next block.



Performance testing:

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

