#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>
#include <errno.h>



int sigint_count = 0;

void sigint_handler(int sign)
{
    if (sign == SIGINT)
    {
        sigint_count++;
        printf("\a");
    }
}

void sigquit_handler(int sign)
{
    if (sign == SIGQUIT) {
        printf("\nReceived SIGQUIT. Total SIGINT signals: %d\n", sigint_count);
        exit(EXIT_SUCCESS);
    }
}

int main() {
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("Error setting up SIGINT handler");
        exit(EXIT_FAILURE);
    }
    if (signal(SIGQUIT, sigquit_handler) == SIG_ERR)
    {
        perror("Error setting up SIGQUIT handler");
        exit(EXIT_FAILURE);
    }
    while (1)
    {
        sleep(1);
    }

    return 0;
}