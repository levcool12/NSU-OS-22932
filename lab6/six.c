#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>



typedef struct Line 
{
    int cnt;
    int cap;
    int* arr;
}line;

void vecAdd(vec* v, int val) {
    if (v->cnt + 1 >= v->cap) {
        v->arr = realloc(v->arr, v->cap * 2 * sizeof(int));
        if (v->arr == NULL) {
            fprintf(stderr, "malloc error: can't allocate memory\n");
            exit(-1);
        }
    }
    v->arr[v->cnt++] = val;
}

int fd;
line nlines;
char buff[256];


void sigalarm(int sig) {

    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek to the beginning of file");
        exit(-1);
    }

    for (int i = 1; i < nlines.cnt; i++) {
        printf("%d ", i);
        int cnt_to_read = nlines.arr[i] - nlines.arr[i - 1];
        while (cnt_to_read > BUFF_SIZE - 1) {

            if (read(fd, buff, BUFF_SIZE - 1) == -1) {
                perror("separate string read");
                exit(-1);
            }
            buff[BUFF_SIZE - 1] = 0;
            printf("%s", buff);

            cnt_to_read -= BUFF_SIZE - 1;
        }

        if (read(fd, buff, cnt_to_read) == -1) {
            perror("separate string read");
            exit(-1);
        }
        buff[cnt_to_read] = 0;
        printf("%s", buff);

    }

    

}

int main(int argc, char* argv[]) {

    
    fd = open(argv[1], O_RDONLY);

   
    if (fd == -1) {
        fprintf(stderr, "Usage: 6 [filename]\n");
        perror("open");
        exit(-1);
    }

    
    nlines.cnt = 0; nlines.cap = 5; nlines.arr = malloc(5 * sizeof(int));


    if (nlines.arr == NULL) {
        fprintf(stderr, "malloc error: can't allocate memory\n");
        exit(-1);
    }

    vecAdd(&nlines, -1);

    
    {
        int string_len;
        for (int cur_file_pos = 0; string_len = read(fd, buff, BUFF_SIZE - 1); cur_file_pos += string_len) {    //iterates while not a file end

            if (string_len == -1) {
                perror("whole file reading");
                exit(-1);
            }

            for (int i = 0; i < string_len; i++) {
                if (buff[i] == '\n') {
                    vecAdd(&nlines, cur_file_pos + i);
                }
            }

        }
    }

    if (sigset(SIGALRM, sigalarm) == SIG_ERR) {
        perror("sigset");
        exit(-1);
    }
    alarm(5);

    printf("Enter a number of string to get:\n");

    int string_num = 0;
    while (1) {
        scanf("%d", &string_num);
        sigset(SIGALRM, SIG_IGN);

        if (string_num == 0) break;

        if (string_num >= nlines.cnt || string_num < 0) {
            printf("Picked line is out of file: it has only %d of strings. ", nlines.cnt - 1);
            printf("Please, enter a value >= 0 and <= %d:\n", nlines.cnt - 1);
            continue;
        }

        if (lseek(fd, nlines.arr[string_num - 1] + 1, SEEK_SET) == -1) {
            perror("lseek");
            exit(-1);
        }

        int cnt_to_read = nlines.arr[string_num] - nlines.arr[string_num - 1];
        while (cnt_to_read > size - 1) {

            if (read(fd, buff, size - 1) == -1) {
                perror("separate string read");
                exit(-1);
            }
            buff[size - 1] = 0;
            printf("%s", buff);

            cnt_to_read -= size - 1;
        }

        if (read(fd, buff, cnt_to_read) == -1) {
            perror("separate string read");
            exit(-1);
        }
        buff[cnt_to_read] = 0;
        printf("%s", buff);

    }

    return 0;

}
