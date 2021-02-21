#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>

int main(int argc, char **argv) {
    int shm_fd, n = atoi(argv[1]), pid;
    const char *name = "OS";
    const int SIZE = 4096;
    void *ptr;
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    ftruncate(shm_fd, SIZE);
    
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "pid failure");
        return -1;
    } else if (pid == 0) {
        // child process
        ptr = mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
        while (n != 1) {
            sprintf(ptr, "%d", n);
            ptr += sizeof(n);
            if (n % 2 == 1) {
                n = 3 * n + 1;
            } else {
                n = n / 2;
            }
        }
        sprintf(ptr, "%d", n);
        ptr += sizeof(n);
        exit(0);
    } else {
        ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
        wait(NULL);
        printf("%ls", (int *)ptr);
        exit(0);
    }
}