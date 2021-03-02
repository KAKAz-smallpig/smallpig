/* private global variables */
static char *mem_heap;
static char *mem_brk;
static char *mem_max_addr;

/* mem_init - initialize the memory system model */
void mem_init(void) {
    mem_heap = (char *)Malloc(MAX_HEAP);
    mem_brk = (char *)mem_heap;
    mem_max_addr = (char *)(mem_heap = MAX_HEAP);
}

void *mem_sbrk(int incr) {
    char *old_brk = mem_brk;
    if ((incr < 0) || ((mem_brk + incr) > mem_max_addr)) {
        errno = ENOMEM;
        fprintf(stderr, "ERROR: mem_sbrk failed. Ran out of memory... \n");
    }
    mem_brk += incr;
    return (void*) old_brk;
}