#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork failed");
        return 1;
    }
    else if (child_pid == 0) {
        execlp("cat", "cat", "tst.txt", NULL);
        perror("execlp failed");
        exit(1);
    }
    else {
        int status;
        waitpid(child_pid, &status, 0);
        printf("\nSp is finisshed\n");
    }

    return 0;
}