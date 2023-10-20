#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h> 

#define MAX_LINE_LENGTH 100
int fd;
void MyAlarm(int var)
{
    lseek(fd, 0, SEEK_SET);
    char buffer[MAX_LINE_LENGTH];
    while ((read(fd, buffer, MAX_LINE_LENGTH)) > 0) {
        printf("%s", buffer);
    }
    _Exit(0);
}

int main() {
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }


    off_t* offsets = (off_t*)malloc(sizeof(off_t));
    int* lengths = (int*)malloc(sizeof(int));
    offsets[0] = 0;
    lengths[0] = 0;
    int lineNumber = 1;

    char buffer[MAX_LINE_LENGTH];
    int count_of_bites;
    int totalLength = 0;
    int i;
    while ((count_of_bites = read(fd, buffer, MAX_LINE_LENGTH)) > 0) {
        for (i = 0; i < count_of_bites; i++) {
            totalLength++;
            if (buffer[i] == '\n') {
                offsets = (off_t*)realloc(offsets, (lineNumber + 1) * sizeof(off_t));
                lengths = (int*)realloc(lengths, (lineNumber + 1) * sizeof(int));
                offsets[lineNumber] = totalLength;
                lengths[lineNumber - 1] = offsets[lineNumber] - offsets[lineNumber - 1] - 1;
                lineNumber++;
            }
        }
    }
    lengths[lineNumber - 1] = totalLength - offsets[lineNumber - 1];

    signal(SIGALRM, MyAlarm);
    alarm(5);

    int lineNum;
    while (1) {
        scanf("%d", &lineNum);

        if (lineNum == 0) break;
        alarm(0);
        if (lineNum < 1 || lineNum > lineNumber) printf("Invalid line number\n");
        else {
            off_t position = lseek(fd, offsets[lineNum - 1], SEEK_SET);
            if (position < 0) {
                perror("Positioning error in file");
                exit(EXIT_FAILURE);
            }

            char line[lengths[lineNum - 1] + 1];
            int bytes = read(fd, line, lengths[lineNum - 1]);
            if (bytes < 0) {
                perror("Error reading line from file");
                exit(EXIT_FAILURE);
            }
            line[lengths[lineNum - 1]] = '\0';

            printf("%s\n", line);
        }
    }

    close(fd);
    free(offsets);
    free(lengths);
    return 0;
}