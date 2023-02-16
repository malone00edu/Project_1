#ifndef PROJECT_1_MYMALLOC_H
#define PROJECT_1_MYMALLOC_H
#endif //PROJECT_1_MYMALLOC_H

#define malloc(s) mymalloc(s, __FILE__, __LINE__);
#define free(p) myfree(p, __FILE__, __LINE__);

static char memory[4096];

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);