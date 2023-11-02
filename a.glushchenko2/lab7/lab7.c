#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <signal.h>

#define MAX_LINE_LENGTH 100

struct stat myStat;
int length = 0;
int file = 0;

void MyAlarm(int var) {
    fstat(file, &myStat);
    off_t sizeFile = myStat.st_size;

    char* buf = (char*)mmap(NULL, sizeFile, PROT_READ, MAP_PRIVATE, file, 0);
    fwrite(buf, sizeof(char), sizeFile, stdout);
    printf("\nYour time is out");
    exit(0);
}

int main(int argc, char* argv[]) {
    file = open(argv[1], O_RDONLY);
    if (file == -1) {
        perror("File open error");
        exit(1);
    }

    fstat(file, &myStat);
    off_t sizeFile = myStat.st_size;
    char* buf = (char*)mmap(NULL, sizeFile, PROT_READ, MAP_PRIVATE, file, 0);

    off_t file_size = sizeFile;
    length = file_size;

    char* buffer = (char*)mmap(NULL, file_size, PROT_READ, MAP_PRIVATE, file, 0);

    int nline = 1;
    int lens[100];
    int ind[100];

    for (int i = 0; i < file_size; i++) {
        if (nline > 1 && buffer[i] == '\n') {
            ind[nline] = i + 1;
            lens[nline] = ind[nline] - ind[nline - 1] - 1;
            nline += 1;
        }
        else if (buffer[i] == '\n' && nline == 1) {
            lens[0] = 0;
            ind[0] = 0;
            ind[1] = i + 1;
            lens[1] = i;
            nline += 1;
        }
    }
    ind[nline] = file_size;
    lens[nline] = ind[nline] - ind[nline - 1];

    signal(SIGALRM, MyAlarm);

    alarm(5);

    while (1) {
        int num_line;
        if (scanf("%d", &num_line) != 1) {
            perror("Scanf error");
            exit(1);
        }

        alarm(5);

        if (num_line == 0) {
            break;
        }
        else if (num_line < 1 || num_line > nline) {
            fwrite("Invalid number of line\n", sizeof(char), 23, stdout);
        }
        else {
            fwrite(buffer + ind[num_line - 1], sizeof(char), lens[num_line], stdout);
            fwrite("\n", sizeof(char), 1, stdout);
        }
    }

    munmap(buffer, file_size);
    close(file);

    return 0;
}