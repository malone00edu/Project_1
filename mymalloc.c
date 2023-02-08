#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "mymalloc.h"

struct meta {
    size_t size;
    struct meta *next;
    struct meta *prev;
    bool reserved;
};

static struct meta *head = NULL;

struct meta *seek_space(size_t size) {

    struct meta *current = head;
    while(current){
        if(current->reserved == false && current->size >= size){
            break;
        }
        if(!current->next){
            current = NULL;
            break;
        }
        current = current->next;
    }
    return current;

}

struct meta *create_space(struct meta *current_block, size_t size){

    if(!current_block){ // If head is NULL. Initialize MEMORY_SIZE.
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
    // If size of requested space is less than current block size.
    // Extract extra space from current block size and create new freed space with this extra.
    // Mark as free space as not reserved.
    if(current_block->size > size + sizeof(struct meta)){
        // Obtain the address of the new block.
        struct meta *new_block = (struct meta*) ((void*) current_block + sizeof(struct meta) + size);
        new_block->size = current_block->size - size - META_SIZE;
        new_block->reserved = false;
        new_block->next = current_block->next;
        new_block->prev = current_block;

        // Allocate space with exact requested size and mark as reserved.
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
    if(!head){// If head is equal to NULL.
        meta_ptr = create_space(NULL, size);
        if(!meta_ptr){// If returned pointer is equal to NULL.
            fprintf(stderr,
                    "Insufficient spaced for requested size. FILENAME: %s, LINE: %d", file, line);
            return NULL;
        }
        return  meta_ptr;
    }
    meta_ptr = seek_space(size);
    if(!meta_ptr){
        fprintf(stderr,
                "Insufficient spaced for requested size. FILENAME: %s, LINE: %d", file, line);
        return NULL;
    }
    meta_ptr = create_space(meta_ptr, size);
    return meta_ptr;

}
void myfree(void *ptr, char *file, int line){

}


