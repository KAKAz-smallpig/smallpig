#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_LINE 80 /* The maximum length command */

/* never test before */

int division_line(char **argv, char *commandline);

int main(void) {
    char *args[MAX_LINE/2 + 1]; /* command line arguments */
    char command_line[80];
    int parallel_run = 0;
    int should_run = 1;
    while (should_run) {
        printf("\nosh> ");
        fflush(stdout);
        read(STDIN_FILENO, command_line, MAX_LINE);
        parallel_run = division_line(args, command_line); //parse commandline
        int pid;
        pid = fork();
        if (pid < 0) {
            fprintf(stderr, "failure fork()");
            return -1;
        } else if (pid == 0) {
            //child process
            execvp(args[0], args);
            exit(0);
        } else {
            //father process
            if (parallel_run != 1) {
                wait(NULL);
            }
            // continue
        }
    }
    return 0;
}

int division_line(char **argv, char *commandline) {
    char *buf;
    int argc = 0, bg; // if run in background (parallel) return 1 else return 0
    strcpy(buf, commandline);
    while (*buf && (*buf == ' '))  {
        buf++;            /* ignore space */
    }
    char *index = strchr(buf, ' ');
    while (index != NULL) {
        argv[argc++] = buf;
        index = '\0';
        buf = index + 1;
        while (*buf && (*buf == ' ')) {
            buf++;        /* ignore space */
        }
        char *index = strchr(buf, ' ');
    }
    argv[argc] = NULL;
    if (argv[argc - 1][0] == '&') {
        bg = 1; //run in background
    } else {
        bg = 0;
    }
    return bg;
}
