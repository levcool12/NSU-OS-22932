#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#define MAX_LINE_LENGTH 40
#define CTRL_D 4
#define CTRL_W 23
#define ERASE 127
#define KILL 21
#define CTRL_G 7

void setup_terminal() {
    struct termios new_termios;
    tcgetattr(0, &new_termios);
    new_termios.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &new_termios);
}

void beep() {
    putchar(CTRL_G);
    fflush(stdout);
}

void erase_last_char(char *buffer, int *position) {
    if (*position > 0) {
        (*position)--;
        putchar('\b');
        putchar(' ');
        putchar('\b');
        fflush(stdout);
    } else {
        beep();
    }
}

void kill_line(char *buffer, int *position) {
    while (*position > 0) {
        (*position)--;
        putchar('\b');
        putchar(' ');
        putchar('\b');
        fflush(stdout);
    }
}

void kill_word(char *buffer, int *position) {
    while (*position > 0 && buffer[*position - 1] == ' ') {
        erase_last_char(buffer, position);
    }
    while (*position > 0 && buffer[*position - 1] != ' ') {
        erase_last_char(buffer, position);
    }
}

int main() {
    setup_terminal();

    char buffer[MAX_LINE_LENGTH + 1];
    int position = 0;

    while (1) {
        char c = getchar();

        if (c == EOF) {
            if (position == 0) {
                putchar('\n');
                break;
            } else {
                beep();
                continue;
            }
        }

        if (c == CTRL_W) {
            kill_word(buffer, &position);
        } else if (c == ERASE) {
            erase_last_char(buffer, &position);
        } else if (c == KILL) {
            kill_line(buffer, &position);
        } else if (c == '\n' || position == MAX_LINE_LENGTH) {
            putchar('\n');
            fflush(stdout);
            position = 0;
        } else {
            buffer[position++] = c;
            putchar(c);
            fflush(stdout);
        }

        beep();
    }

    return 0;
}
