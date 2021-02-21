#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
    if (argc < 2) {
        fprintf(stderr, "You should put number in");
        return -1;
    }
    int pid, n = atoi(argv[1]);
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failure");
        return -1;
    } else if (pid == 0) {
        // child process
        while (n != 1) {
            printf("%d, ", n);
            if (n % 2 == 1) {
                n = 3 * n + 1;
            } else {
                n = n / 2;
            }
        }
        printf("%d\n", n);
        exit(0);
    } else {
        //parent process
        printf("parent process wait number %d\n", n);
        wait(NULL);
        printf("parent process down");
        exit(0);
    }
}