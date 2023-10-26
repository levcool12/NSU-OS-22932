#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char* argv[]) {

    int file = open(argv[1], O_RDONLY);
    char buffer[MAX_LINE_LENGTH];

    int length = 0, nline = 1, rd, num_line;
    int lens[100];
    int ind[100];
    lens[0] = 0;
    ind[0] = 0;


    while ((rd = read(file, buffer, MAX_LINE_LENGTH)) > 0) {
        for (int i = 0; i < rd; i++)
        {
            length += 1;
            if (nline > 1 && buffer[i] == '\n') {
                ind[nline] = length;
                lens[nline] = ind[nline] - ind[nline - 1] - 1;
                nline += 1;
            }
            else if (buffer[i] == '\n' && nline == 1) {
                ind[1] = length;
                lens[1] = i;
                nline += 1;
            }

        }
    }
    ind[nline] = length;
    lens[nline] = ind[nline] - ind[nline - 1];


    while (1) {
        scanf("%d", &num_line);
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