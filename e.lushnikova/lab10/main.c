#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error when creating subprocess\n");
        exit(1);
    }
    else if (pid == 0) {
        execvp(argv[1], argv + 1);
    }
    else {
        int status;
        wait(NULL);
        int exitcode = WEXITSTATUS(status);
        printf("Exit code: %d\n", exitcode);
    }

    return 0;
}