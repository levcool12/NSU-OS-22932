#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void File_Open(char *file) {
    FILE *f = fopen(file, "r");
    if (f == NULL) { perror("can't open the file\n"); return; }
    fclose(f);
}

int main(int argc, char **argv) {
    if (argc < 2) { printf("file name not specified\n"); return 1; }

    printf( " uid: %d euid: %d\n", getuid(), geteuid() );
    File_Open(argv[1]);

    setuid(getuid());

    printf( " uid: %d euid: %d\n", getuid(), geteuid() );
    File_Open(argv[1]);

    return 0;
}