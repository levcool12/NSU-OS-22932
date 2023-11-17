#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == -1) {
        printf("Error when creating subprocess\n");
        exit(1);
    }
    else if (pid == 0) {
        execlp("cat", "cat", "file.txt", NULL);
    }
    else {
        printf("Process is finished\n");
        wait(NULL);
    }

    return 0;
}