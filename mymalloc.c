#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "mymalloc.h"

// The structure that holds all relevant metadata.
struct meta {
    size_t size;
    struct meta *next;
    struct meta *prev;
    bool reserved;
};
// The head of the linked list.
static struct meta *head = NULL;

// Finds appropriate space for requested size.
struct meta *find_space(size_t size) {

    struct meta *current = head;
    while(current){
        // First suitable size to be found will force an exit of the loop.
        if(current->reserved == false && current->size >= size){
            break;
        }
        // If no suitable size is found, loop will end with current = NULL.
        if(!current->next){
            current = NULL;
            break;
        }
        current = current->next;
    }
    return current;

}

// Allocates space for requested size.
struct meta *allocate_space(struct meta *current_block, size_t size){

    // If head is NULL. Initialize entirety of MEMORY_SIZE in memory array.
    if(!current_block){
        head = (struct meta*) memory;
        head->size = MEMORY_SIZE - META_SIZE;
        head->next = NULL;
        head->prev = NULL;
        head->reserved = false;
        current_block = head;
    }
    // If size of requested space is equal to current block size.
    if(current_block->size == size){
        current_block->size = size;
        current_block->reserved = true;
        return (void*) current_block + META_SIZE;
    }
    /*
     * If size of requested space is less than current block size.
     * Extract extra space from current block size and create new freed space with this extra space.
     * Mark new freed space as not reserved.
     */
    if(current_block->size > size + sizeof(struct meta)){
        // Obtain the address of the new block.
        struct meta *new_block = (struct meta*) ((void*) current_block + sizeof(struct meta) + size);
        new_block->size = current_block->size - size - META_SIZE;
        new_block->reserved = false;
        new_block->next = current_block->next;
        new_block->prev = current_block;

        /*
         * The remaining space of the current block should now equal the requested space.
         * Use this remaining space of the current block to allocate the exact
         * requested size and mark as reserved.
         */
        current_block->size = size;
        current_block->reserved = true;
        current_block->next = new_block;
        return (void*) current_block + META_SIZE; //Return exact position for user data.
    }
}

void *mymalloc(size_t size, char *file, int line){

    struct meta *meta_ptr;
    if(size <= 0){
        return NULL;
    }
    /*
     * If head is equal to NULL.
     * Initialize the head of the linked list and return pointer.
     */
    if(!head){
        meta_ptr = allocate_space(NULL, size); // Allocate space.
        if(!meta_ptr){// If returned pointer is equal to NULL.
            fprintf(stderr,
                    "Insufficient space for requested size. FILENAME: %s, LINE: %d\n", file, line);
            return NULL;
        }
        return  meta_ptr;
    }
    meta_ptr = find_space(size); //Find the appropriate space for requested size.
    if(!meta_ptr){
        fprintf(stderr,
                "Insufficient space for requested size. FILENAME: %s, LINE: %d\n", file, line);
        return NULL;
    }
    meta_ptr = allocate_space(meta_ptr, size);
    return meta_ptr;

}
void myfree(void *ptr, char *file, int line){}



