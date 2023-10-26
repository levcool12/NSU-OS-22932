#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 100

int main() {
    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("File opening error");
        exit(1);
    }
    off_t offsets[MAX_LINE_LENGTH];
    int lengths[MAX_LINE_LENGTH];
    char buffer[MAX_LINE_LENGTH];
    int line_count = 0;
    offsets[line_count] = lseek(fd, 0L, SEEK_CUR);
    while (read(fd, buffer, 1) > 0) {
        if (buffer[0] == '\n') {
            lengths[line_count] = lseek(fd, 0L, SEEK_CUR) - offsets[line_count];
            line_count++;
            offsets[line_count] = lseek(fd, 0L, SEEK_CUR);
        }
    }
    int line_number;
    while (1) {
        printf("Enter line number (0 to exit): ");
        scanf("%d", &line_number);

        if (line_number == 0) {
            break;
        }

        if (line_number < 0 || line_number > line_count) {
            printf("Invalid line number\n");
            continue;
        }

        lseek(fd, offsets[line_number - 1], SEEK_SET);
        read(fd, buffer, lengths[line_number - 1]);
        buffer[lengths[line_number - 1]] = '\0';

        printf("%s\n", buffer);
    }
    close(fd);
    return 0;
}
