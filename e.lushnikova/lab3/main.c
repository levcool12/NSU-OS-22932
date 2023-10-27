#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main() {
    uid_t ruid, euid;
    FILE* fp;

    fp = fopen("file", "w+");
    if (fp == NULL) {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }

    ruid = getuid();
    euid = geteuid();
    printf("Real user id: %d\n", ruid);
    printf("Effective user id: %d\n", euid);

    if (setuid(geteuid()) == -1) {
        perror("Couldn't open the file");
        exit(EXIT_FAILURE);
    }

    ruid = getuid();
    euid = geteuid();
    printf("Real user id: %d\n", ruid);
    printf("Effective user id: %d\n", euid);

    fclose(fp);

    return 0;
}