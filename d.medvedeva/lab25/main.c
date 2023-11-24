#include <stdio.h>
#include <unistd.h>
#include <sys/param.h>
#include <string.h>

int main() {
    char cwd[MAXPATHLEN];
    getcwd(cwd, MAXPATHLEN);
    char* command = strcat(cwd, "/to_upper");
    FILE* pipe_writer = popen(command, "w");
    if (pipe_writer == NULL) {
        write(2, "Couldn't create a pipe", 23);
        return 1;
    }
    fputs("SoMe INTErestING TexT", pipe_writer);
    pclose(pipe_writer);
    return 0;
}
