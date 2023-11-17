#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    pid_t child_pid = fork();
    if (argc < 2) {
        printf("Not enough arguments\n");
        exit(0);
    }
    else if (child_pid == -1) {
        perror("fork failed");
        return 1;
    }
    else if (child_pid == 0) {
        execvp(argv[1], argv + 1);
        exit(0);
    }
    else {
        int status;
        waitpid(child_pid, &status, 0);
        if (WIFEXITED(status)) {
            printf("Child process ended with code %d\n", WEXITSTATUS(status));
        }
        else {
            printf("Child process's finishing was unsuccessfull\n");
        }
    }

    return 0;
}
