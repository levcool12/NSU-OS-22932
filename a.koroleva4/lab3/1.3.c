#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    FILE* file;
    uid_t real_uid, effective_uid;

    printf("Real UID: %d\n", getuid());
    printf("Effective UID: %d\n", geteuid());

    file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }
    fclose(file);

    setuid(getuid());

    file = fopen("data.txt", "r");
    if (file == NULL) {
        perror("Cannot open file");
        exit(EXIT_FAILURE);
    }
    fclose(file);

    return 0;
}
