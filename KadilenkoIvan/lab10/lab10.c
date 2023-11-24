#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "error %s command \n", argv[0]);
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    if (child_pid == -1) {
        perror("Error calling fork");
        exit(EXIT_FAILURE);
    }
    if (child_pid == 0) {
            if (execvp(argv[1], &argv[1]) == -1) {
            perror("Error calling execvp");
            exit(EXIT_FAILURE);
        }
    } 
    else { 
        int status;
        if (waitpid(child_pid, &status, 0) == -1) {
            perror("Error calling waitpid");
            exit(EXIT_FAILURE);
        }
        if (WIFEXITED(status)) {
            printf("Child process exited with code %d\n", WEXITSTATUS(status));
        } 
	else {
            printf("Child process exited not normally\n");
        }
    }

    return 0;
}
