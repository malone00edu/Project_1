#ifndef PROJECT_1_MYMALLOC_H
#define PROJECT_1_MYMALLOC_H
#endif //PROJECT_1_MYMALLOC_H

#define malloc(s) mymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

// The heap that will be used by our implementation of malloc and free.
static char memory[4096];

// Modified version of malloc and free. Errors will be displayed to the console.
void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);