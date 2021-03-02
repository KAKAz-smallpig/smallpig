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

#define BUFFSIZE 1024
#define READ_END 0
#define WRITE_END 1

char convert(char character) {
    if (character >= 97) {
        return character - 32;
    } else {
        return character + 32;
    }
}

int main(int argc, char **argv) {
    int pid, fd[2], other_fd[2];
    char write_message[BUFFSIZE], read_message[BUFFSIZE];
    strcpy(write_message, argv[1]);
    //create pipe
    if (pipe(fd) == -1 || pipe(other_fd) == -1) {
        fprintf(stderr, "pipe failure");
        return -1;
    }
    pid = fork();
    if (pid == -1) {
        fprintf(stderr, "fork failure");
        return -1;
    } else if (pid == 0) {
        //child process
        close(fd[WRITE_END]);
        read(fd[READ_END], read_message, BUFFSIZE);
        close(fd[READ_END]);
        printf("child process read: %s\n", read_message);
        int length = strlen(read_message);
        for (int n = 0; n < length; n++) {
            write_message[n] = convert(read_message[n]);
        }
        close(other_fd[READ_END]);
        write(other_fd[WRITE_END], write_message, BUFFSIZE);
    } else {
        //parent process
        close(fd[READ_END]);
        write(fd[WRITE_END], write_message, BUFFSIZE);
        close(fd[WRITE_END]);
        close(other_fd[WRITE_END]);
        read(other_fd[READ_END], read_message, BUFFSIZE);
        printf("return_message: %s\n", read_message);
        close(other_fd[READ_END]);
        exit(0);
    }
}