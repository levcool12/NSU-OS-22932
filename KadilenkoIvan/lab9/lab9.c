#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(1);
    }
    if (pid == 0) {
        execlp("cat", "cat", "file.txt", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } 
    else {
        printf("This is the parent process.\n");
        int status;
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        if (WIFEXITED(status)) {
            printf("\nChild process exited with status %d.\n", WEXITSTATUS(status));
        } 
	else {
            printf("\nChild process did not terminate normally.\n");
        }
    }

    return 0;
}
