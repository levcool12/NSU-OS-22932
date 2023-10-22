#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>

int execvpe(const char *file, char *const argv[], char *const envp[]) {
    extern char **environ;

    if (envp != NULL) {
        environ = envp;
    }

    return execvp(file, argv);
}

int main() {
    char *const cmd[] = {"ls", "-l", NULL};
    char *const env[] = {"USER=customuser", NULL};

    execvpe("/bin/ls", cmd, env);

    perror("execvpe"); // This line will be executed only if execvpe fails
    return 1;
}

