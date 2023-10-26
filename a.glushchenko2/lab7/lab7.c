#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define MAX_LINE_LENGTH 100

int file = 0;
int length = 0;
struct stat myStat;

void MyAlarm(int var) {
    char* buffer = (char*)malloc(sizeof(char) * length);
    fstat(file, &myStat);
    char* map = mmap(NULL, myStat.st_size, PROT_READ, MAP_PRIVATE, file, 0);
    printf("Your time is out\n");
    printf("%s\n", map);
    munmap(map, myStat.st_size);
    exit(0);
}

int main(int argc, char* argv[]) {
    file = open(argv[1], O_RDONLY);
    char buffer[MAX_LINE_LENGTH];

    int nline = 1, num_line;
    int lens[100];
    int ind[100];

    struct stat myStat;
    fstat(file, &myStat);
    char* map = mmap(NULL, myStat.st_size, PROT_READ, MAP_PRIVATE, file, 0);

    for (int i = 0; i < myStat.st_size; i++) {
        length += 1;
        if (nline > 1 && map[i] == '\n') {
            ind[nline] = length;
            lens[nline] = ind[nline] - ind[nline - 1] - 1;
            nline += 1;
        }
        else if (map[i] == '\n' && nline == 1) {
            lens[0] = 0;
            ind[0] = 0;
            ind[1] = length;
            lens[1] = i;
            nline += 1;
        }
    }
    ind[nline] = length;
    lens[nline] = ind[nline] - ind[nline - 1];

    signal(SIGALRM, MyAlarm);

    alarm(5);

    while (1) {
        scanf("%d", &num_line);

        alarm(5);

        if (num_line == 0) {
            break;
        }
        else if (num_line < 1 || num_line > nline) {
            perror("Invalid number of line");
        }
        else {
            char* line = (char*)malloc(sizeof(char) * (lens[num_line] + 1));
            lseek(file, ind[num_line - 1], SEEK_SET);
            read(file, line, lens[num_line]);
            line[lens[num_line]] = '\0';
            printf("%s\n", line);
            free(line);
        }
    }

    munmap(map, myStat.st_size);
    close(file);
    return 0;
}