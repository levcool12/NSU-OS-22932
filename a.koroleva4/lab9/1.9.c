#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Error creating subprocess");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0) {
        execlp("cat", "cat", "test.txt", NULL);
    }
    else {
        int status;
        wait(&status);
        printf("Work completed\n");
    }

    return 0;
}