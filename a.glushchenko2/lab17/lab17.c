#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <sys/termios.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 41

int main() {
    struct termios initial_settings;
    struct termios new_settings;

    tcgetattr(STDIN_FILENO, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO; 

    new_settings.c_cc[VMIN] = 1;

    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);

    char c;
    char* input = (char*)malloc(MAX_LINE_LENGTH * sizeof(char));
    int len = 0;
    char s = '\n';

    while (read(0, &c, 1)) {
        if (len > 0 && c == CERASE) {
            len -= 1;
            input[len] = '\0';
            printf("\33[D\33[K");
            fflush(stdout);
        }

        else if (c == CEOF && input[0] == '\0') {
            break;
            exit(0);
        }

        else if (c == CKILL) {
            len = 0;
            input[0] = '\0';
            printf("\33[2K\r");
            fflush(stdout);
            break;
        }

        else if (c == CWERASE) {
            int i = len - 1;
            while (i >= 0 && input[i] == ' ') {
                i--;
            }
            while (i >= 0 && input[i] != ' ') {
                i--;
            }
            input[len - i] = '\0';

            printf("\033[%dD\033[K", len - i - 1);
            fflush(stdout);
        }

        else if (isprint(c) == 0) {
            putchar('\a');
            fflush(stdout);
        }

        else {
            if (len == MAX_LINE_LENGTH) {
                write(1, &s, 1);
                len = 0;
            }

            input[len++] = c;
            input[len] = '\0';
            write(1, &c, 1);
        }
    }
    fflush(stdout);
    tcsetattr(0, TCSANOW, &initial_settings);
    return 0;
}