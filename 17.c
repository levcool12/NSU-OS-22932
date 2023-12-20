#include <unistd.h>
#include <sys/termios.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/ttydefaults.h>
#include <string.h>

#define LINE_LENGTH 40
struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();

    char c;
    static char line[LINE_LENGTH + 1];

    while (read(STDIN_FILENO, &c, 1) == 1) {
        int len = strlen(line);
        if (iscntrl(c) || !isprint(c)) {
            switch (c) {
            case CERASE: {
                line[len - 1] = 0;

                printf("\33[D\33[K");

                break;
            }

            case CKILL: {

                line[0] = 0;

                printf("\33[2K\r");

                break;
            }

            case CWERASE: {

                int word_start = 0;
                char prev = ' ';
                for (int i = 0; i < len; i++) {
                    if (line[i] != ' ' && prev == ' ') {
                        word_start = i;
                    }
                    prev = line[i];
                }

                line[word_start] = 0;

               printf("\33[%dD\33[K", len - word_start);

                break;
            }

            case CEOF: {
               
                if (line[0] == 0) { exit(0); }
                break;
            }

            default: {
               
                putchar('\a');
                break;
            }
            }
        }
        else {
            if (len == LINE_LENGTH) {
                putchar('\n');
                len = 0;
            }

            line[len++] = c;
            line[len] = 0;

            putchar(c);
        }

        fflush(NULL);
    }

    return 0;
}