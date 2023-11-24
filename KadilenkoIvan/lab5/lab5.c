#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    int fd, count = 0, count_n = 1, capacity = 2, capacity_n = 2, line = 0;
    char symbol = '\0';
    ssize_t check;
    char* buf = (char*)malloc(sizeof(char) * 2);
    int* buf_n = (int*)malloc(sizeof(int) * 2);
    buf_n[0] = '\0';

    if ((fd = open(argv[1], 0)) == -1) {
        perror("Could not open the file: ");
        exit(1);
    }

    while ((check = read(fd, &symbol, 1)) > 0) {
        count++;
        if (count_n == capacity_n) {
            buf_n = (int*)realloc(buf_n, sizeof(int) * capacity_n * 2);
            capacity_n *= 2;
        }
        if (symbol == '\n') {
            buf_n[count_n] = lseek(fd, 0, 1);
            count_n++;
        }
    }
    buf_n[count_n] = lseek(fd, 0, 1);
    count_n++;
    if (capacity < count) {
        buf = (char*)realloc(buf, sizeof(char) * (count + 1));
    }

    lseek(fd, 0, SEEK_SET);
    printf("What line?\n");
    scanf("%d", &line);
    while (line != 0) {
        int len = buf_n[line] - buf_n[line - 1];
        lseek(fd, (long)buf_n[line - 1], 1);
        read(fd, buf, len);
        write(1, buf, len);
A:
        lseek(fd, 0, SEEK_SET);
        printf("\nWhat line?\n");
        scanf("%d", &line);
	
        if (line >= count_n || line < 0) {
            printf("No that line\n");
            goto A;
        }

    }

    free(buf_n);
    free(buf);
    close(fd);
    return 0;;
}