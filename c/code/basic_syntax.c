#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

int main(void) {
    pid_t pid, pid1;
    // fork a child process
    pid = fork();
    if (pid < 0) {
        fprintf(stderr, "fork failed");
        return 1;
    } else if (pid == 0) {
        // child process
        pid1 = getpid();
        printf("child: pid = %d", pid);
        printf("child: pid1 = %d", pid1);
    } else {
        pid1 = getpid();
        printf("parent: pid = %d", pid);
        printf("parent: pid1 = %d", pid1);
        wait(NULL);
    }
    return 0;
}