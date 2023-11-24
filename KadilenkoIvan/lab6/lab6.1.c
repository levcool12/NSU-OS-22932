#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

void handle_alarm(int signum, int count_n, int* buf_n) {
    for (int i = 0; i < count_n, i++)
    {
        int n = i;
        int len = buf_n[line] - buf_n[line - 1];
        lseek(fd, (long)buf_n[line - 1], 1);
        read(fd, buf, len);
        write(1, buf, len);
    }
    exit(0);
}


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

    signal(SIGALRM, handle_alarm);
    int n = 0;
    while (1) {
        lseek(fd, 0, 0);
        printf("What line(programm will close after 5 seconds): \n");
        alarm(5);

        scanf("%d", &n);
        alarm(0);

        if (n >= count_n || n < 0) {
            printf("No that line\n");
            continue;
        }

        if (n == 0) {
            break;
        }

        int len = buf_n[n] - buf_n[n - 1];
        lseek(fd, (long)buf_n[n - 1], 1);
        read(fd, buf, len);
        write(1, buf, len);
    }

    free(buf_n);
    free(buf);
    close(fd);
    return 0;;
}