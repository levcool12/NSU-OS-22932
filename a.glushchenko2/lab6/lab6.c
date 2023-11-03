#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <malloc.h>

#define MAX_LINE_LENGTH 100

int file = 0;
int length = 0;

void MyAlarm(int var) {
    char* buffer = (char*)malloc(sizeof(char) * length);
    off_t a = lseek(file, 0, SEEK_SET);
    read(file, buffer, length);
    printf("Your time is out\n");
    printf("%s\n", buffer);
    exit(0);
}

int main(int argc, char* argv[]) {
    file = open(argv[1], O_RDONLY);
    char buffer[MAX_LINE_LENGTH];

    int nline = 1, rd, num_line;
    int lens[100];
    int ind[100];
    

    while ((rd = read(file, buffer, MAX_LINE_LENGTH)) > 0) {
        for (int i = 0; i < rd; i++) {
            length += 1;
            if (nline > 1 && buffer[i] == '\n') {
                ind[nline] = length;
                lens[nline] = ind[nline] - ind[nline - 1] - 1;
                nline += 1;
            }
            else if (buffer[i] == '\n' && nline == 1) {
                lens[0] = 0;
                ind[0] = 0;
                ind[1] = length;
                lens[1] = i;
                nline += 1;
            }
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
            lseek(file, ind[num_line - 1], SEEK_SET);
            read(file, buffer, lens[num_line]);
            buffer[lens[num_line]] = '\0';
            printf("%s\n", buffer);
        }
    }

    return 0;
}