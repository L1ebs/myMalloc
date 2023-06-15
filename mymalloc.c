#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"

//structure to keep track of allocated memory blocks
typedef struct block {
    size_t size;
    struct block *next;
    int allocated;
    char *file; // track which file and line allocated this block for debugging purposes
    int line;
} block_t;

// define the size of memory pool
#define MEMORY_SIZE 4096
static char memory[MEMORY_SIZE];

// initialize the head of memory blocks to null
static block_t *head = NULL;

// function to allocate memory
static void *mymalloc(size_t size, char *file, int line) {
    // if the head of the block list is null, initialize it to the start
    if (head == NULL) {
        head = (block_t *)memory;
        head->size = MEMORY_SIZE - sizeof(block_t);
        head->next = NULL;
        head->allocated = 0;
        head->file = NULL;
        head->line = -1;
    }

    // search through the list of blocks to find a free block large enough to allocate
    block_t *current = head;
    while (current != NULL) {
        if (!current->allocated && current->size >= size) {
            // mark the block as allocated
            current->allocated = 1;

            // split the block if it is larger than the requested size plus the size of a block_t
            if (current->size >= size + sizeof(block_t) + 1) {
                block_t *new_block = (block_t *)((char *)current + sizeof(block_t) + size);
                new_block->size = current->size - sizeof(block_t) - size;
                new_block->next = current->next;
                new_block->allocated = 0;
                new_block->file = NULL;
                new_block->line = -1;
                current->next = new_block;
                current->size = size;
            }

            // set the file and line information for the block for debugging purposes
            current->file = file;
            current->line = line;

            // return a pointer to the memory block within the block (after the block_t header)
            return (void *)((char *)current + sizeof(block_t));
        }
        current = current->next;
    }

    // if no free block was found, print an error message and return null
    printf("%s:%d: Not enough memory\n", file, line);
    return NULL;
}


static void myfree(void *ptr, char *file, int line) {
    // Check if ptr is NULL
    if (ptr == NULL) {
        printf("%s:%d: Can't free a NULL pointer\n", file, line);
        return;
    }

    // Cast ptr to block_t pointer
    block_t *current = (block_t *)((char *)ptr - sizeof(block_t));

    // Check if ptr is at the start of a block
    if ((char *)ptr != (char *)current + sizeof(block_t)) {
        printf("%s:%d: Pointer is not at start of block\n", file, line);
        return;
    }

    // Check if block is already freed
    if (!current->allocated) {
        printf("%s:%d: Pointer is already freed\n", file, line);
        return;
    }

    // Free the block
    current->allocated = 0;

    // Merge adjacent free blocks
    block_t *prev = NULL;
    block_t *next = current->next;
    while (next != NULL && !next->allocated) {
        current->size += sizeof(block_t) + next->size;
        current->next = next->next;
        next = current->next;
    }
    if (prev != NULL && !prev->allocated) {
        prev->size += sizeof(block_t) + current->size;
        prev->next = current->next;
    }
}

//used for testing to print the memory
static void print_memory() {
    block_t *current = head;
    while (current != NULL) {
        printf("block at %p, size %lu, allocated: %s\n", (void *)current, current->size, current->allocated ? "yes" : "no");
        current = current->next;
    }
}

static void check_memory() {
    int leakCount = 0;
    block_t *current = head;
    while (current != NULL) {
        if (current->allocated) {
            leakCount++;
        }
        current = current->next;
    }
    if (leakCount > 0) {
        printf("Memory leak is detected: %d unfreed block(s)\n", leakCount);
    } 
    else {
        printf("No memory leaks are detected\n");
    }
}