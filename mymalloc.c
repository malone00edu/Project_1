#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "mymalloc.h"

#define META_SIZE sizeof(struct meta);
#define MEMORY_SIZE 4096
#define PTR_FOUND 1
#define PTR_NOT_FOUND -1
#define EMPTY 0

// The structure that holds all relevant metadata.
struct meta {
    size_t size;
    struct meta *next;
    struct meta *prev;
    bool reserved;
};
// The head of the linked list in memory[MEMORY_SIZE].
static struct meta *head = NULL;

// Helper function. Finds appropriate space for requested size.
static struct meta *find_space(size_t size) {

    struct meta *current = head;
    while (current) {
        // First suitable size to be found will force an exit of the loop.
        if (current->reserved == false && current->size >= size + sizeof(struct meta)) {
            break;
        }
        // If no suitable size is found, loop will end with current = NULL.
        if (!current->next) {
            current = NULL;
        }
        current = current->next;
    }
    return current;

}

// Helper function. Allocates space for requested size.
static struct meta *allocate_space(struct meta *currentBlock, size_t size) {

    // If head is NULL. Initialize entirety of MEMORY_SIZE in memory array.
    if (!currentBlock) {
        head = (void *) memory;
        head->size = MEMORY_SIZE - META_SIZE
        head->next = NULL;
        head->prev = NULL;
        head->reserved = false;
        currentBlock = head;

        // If current block size is equal to requested size.
        if (currentBlock->size == size) {
            currentBlock->size = size;
            currentBlock->reserved = true;
            return (void *) currentBlock + META_SIZE;
        }
    }

    // If current block size less than requested size + metadata. Return NULL.
    if (currentBlock->size < size + sizeof(struct meta)) {
        return NULL;
    }

    // If current block size is equal to requested size + metadata.
    if (currentBlock->size == size + sizeof(struct meta)) {
        currentBlock->size = size;
        currentBlock->reserved = true;
        return (void *) currentBlock + META_SIZE;
    }
    /*
     * If current block size is greater than requested size + metadata.
     * Extract extra space from current block size and create new free space with this extra space.
     * Mark new free space as not reserved.
     */
    if (currentBlock->size > size + sizeof(struct meta)) {
        // Obtain the address of the new block.
        struct meta *new_block = (struct meta*) ((char *) currentBlock + sizeof(struct meta) + size);
        new_block->size = currentBlock->size - size - META_SIZE;
        new_block->reserved = false;
        new_block->next = currentBlock->next;
        new_block->prev = currentBlock;
        /*
         * The remaining space of the current block should now equal the requested size + metadata.
         * Use this remaining space of the current block to allocate and mark as reserved.
         */
        currentBlock->size = size;
        currentBlock->reserved = true;
        currentBlock->next = new_block;
        return (void *) currentBlock + META_SIZE;
    }
    return NULL;
}

void *mymalloc(size_t size, char *file, int line) {

    struct meta *metaPtr;
    if (size <= 0) {
        return NULL;
    }
    /*
     * If head is equal to NULL.
     * Initialize the head of the linked list and return pointer.
     */
    if (!head) {
        metaPtr = allocate_space(NULL, size); // Allocate space.
        if (!metaPtr) {// If returned pointer is equal to NULL.
            fprintf(stderr,
                    "Insufficient space for requested size. FILENAME: %s, LINE: %d\n", file, line);
            return NULL;
        }
        return metaPtr;
    }
    metaPtr = find_space(size); //Find the appropriate space for requested size.
    if (!metaPtr) {
        fprintf(stderr,
                "Insufficient space for requested size. FILENAME: %s, LINE: %d\n", file, line);
        return NULL;
    }
    metaPtr = allocate_space(metaPtr, size);
    return metaPtr;

}

/*
 * Helper function. Checks the scope of the heap and cycles through the linked list of
 * pointers to see if the given pointer is valid. Return 1 if the pointer is found.
 * Return -1 if the pointer is not found.
 */
static int find_ptr(struct meta *givenPtr) {
    //printf("========%p\n", head); //Head and memory should be the same. The start of the heap.
    //printf("++++++++%p\n", memory);
    //printf("--------%p\n", memory + MEMORY_SIZE); //Memory + MEMORY_SIZE is the end the of heap.

    // If the given pointer is outside the scope of the heap. Return -1 (PTR_NOT_FOUND).
    if((char*) givenPtr < memory || (char*) givenPtr > memory + MEMORY_SIZE){
        return PTR_NOT_FOUND;
    }
    // Initial location status value = 0 (EMPTY);
    int location_status = EMPTY;
    struct meta *checkPtr = (struct meta*) ((char*) givenPtr - sizeof(struct meta));
    struct meta *currPtr = head;

    // Check all pointers within the linked list. Set status value = 1 (PTR_FOUND) if found.
    // Set to -1 if not found.
    while (currPtr) {
        if (checkPtr == currPtr) {
            location_status = PTR_FOUND;
            break;
        }
        if (!currPtr->next) {
            location_status = PTR_NOT_FOUND;
            break;
        }
        currPtr = currPtr->next;
    }
    return location_status;
}

// free using eager approach
void myfree(void *ptr, char *file, int line) {
    if (!ptr) {
        fprintf(stderr, "Cannot free a null pointer. FILENAME: %s, LINE: %d\n", file, line);
        return;
    }
    // Checks to see if a given pointer exists within the scope of the heap/linked list.
    int result = find_ptr(ptr);
    if (result == -1) {
        fprintf(stderr, "Pointer does not exist within the heap/linked list. "
                        "FILENAME: %s, LINE: %d\n", file, line);
        return;
    }
    //if not null there should be a struct meta header associated with it.
    //retrieves the header by subtracting the size of struct meta from the ptr
    struct meta *metaPtr = (struct meta *) ((char *) ptr - sizeof(struct meta));
    if (!metaPtr->reserved) {
        fprintf(stderr, "Invalid pointer. FILENAME: %s, LINE: %d\n", file, line);
        return;
    }

    metaPtr->reserved = false;
    // Coalesce with previous block if it's free
    if (metaPtr->prev && !metaPtr->prev->reserved) {
        metaPtr->prev->next = metaPtr->next;
        metaPtr->prev->size += sizeof(struct meta) + metaPtr->size;
        if (metaPtr->next) {
            metaPtr->next->prev = metaPtr->prev;
        }
        metaPtr = metaPtr->prev;
    }
    // Coalesce with next block if it's free
    if (metaPtr->next && !metaPtr->next->reserved) {
        metaPtr->size += sizeof(struct meta) + metaPtr->next->size;
        metaPtr->next = metaPtr->next->next;
        if (metaPtr->next) {
            metaPtr->next->prev = metaPtr;
        }
    }
}


