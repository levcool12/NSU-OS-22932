#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <ctype.h>

#define BUFFER_SIZE 40

int main()
{
    struct termios old_termios, new_termios;
    char buffer[BUFFER_SIZE];
    int i = 0;
    char c;

    tcgetattr(STDIN_FILENO, &old_termios);
    new_termios = old_termios;

    new_termios.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    while (1) {
        c = getchar();
        if (c == 27) {
            c = getchar();
            c = getchar();
            if (c == 65) {
                if (i > 0) {
                    i--;
                    printf("\b \b");
                }
            }
        }
        else if (c == 127) {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        }
        else if (c == 23) {
            while (i > 0 && buffer[i - 1] != ' ') {
                i--;
                printf("\b \b");
            }
        }
        else if (c == 4) {
            if (i == 0) {
                break;
            }
        }
        else if (c == '\n') {
            buffer[i] = '\0';
            printf("\n");
            i = 0;
        }
        else if (!isprint(c)) {
            printf("%c", 7);
        }
        else {
            if (i < BUFFER_SIZE - 1) {
                buffer[i] = c;
                i++;
                printf("%c", c);
            }
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);
    return 0;
}