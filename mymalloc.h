#ifndef PROJECT_1_MYMALLOC_H
#define PROJECT_1_MYMALLOC_H
#endif //PROJECT_1_MYMALLOC_H

#define malloc(s) mymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

#ifndef MEMORY_SIZE
#define  MEMORY_SIZE 5000
#endif

#define META_SIZE sizeof(struct meta);

static char memory[MEMORY_SIZE];

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);