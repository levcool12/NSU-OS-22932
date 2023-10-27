#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main() {
    struct termios original_termios, new_termios;
    char c;

    // Save original terminal settings
    tcgetattr(STDIN_FILENO, &original_termios);
    new_termios = original_termios;

    // Disable canonical mode and echo
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    printf("Press a key (without enter)");
    c = getchar();
    // Restore original terminal settings

    printf("\nYou pressed '%c'\n", c);
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    return 0;
}