#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    FILE* fp = fopen("file", "r");
    if (fp == NULL) {
        perror("Open file error");
        exit(EXIT_FAILURE);
    }

    printf("Real user ID: %d\n", getuid());
    printf("Effective user ID: %d\n", geteuid());

    if (setuid(geteuid()) == -1) {
        perror("User ID set error");
        exit(EXIT_FAILURE);
    }
    printf("Real user ID: %d\n", getuid());
    printf("Effective user ID: %d\n", geteuid());

    fclose(fp);

    return 0;
}