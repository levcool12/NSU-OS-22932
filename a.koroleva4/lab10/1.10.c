#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    pid_t pid;

    if (argc < 2) {
        printf("You must specify the command to execute\n");
        return 1;
    }

    pid = fork();
    if (pid < 0) {
        printf("Error creating child process\n");
        return 1;
    }
    else if (pid == 0) {
        if (execvp(argv[1], argv + 1) == -1) {
            printf("Error executing command\n");
            return 1;
        }
    }
    else {
        int status;
        waitpid(pid, &status, 0);
        printf("Completion code: %d\n", WEXITSTATUS(status));
    }

    return 0;
}
