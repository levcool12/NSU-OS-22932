#include <unistd.h>
#include <stdio.h>

void tryToOpen(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open the file\n");
        return;
    }
    fclose(file);
}

int main(int argc, char **argv) {
    if (argc == 1) {
        printf("Filename is not specified\n");
        return 1;
    }
    if (argc > 2) {
        printf("You need one argument");
        return 1;
    }

    printf("uid: %d, euid: %d\n", getuid(), geteuid());
    tryToOpen(argv[1]);

    setuid(getuid());

    printf("uid: %d, euid: %d\n", getuid(), geteuid());
    tryToOpen(argv[1]);

    return 0;
}
