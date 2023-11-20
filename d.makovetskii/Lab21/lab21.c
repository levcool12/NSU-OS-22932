// 21. Пищалка
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int count = 0;  // счетчик сигналов

void handleSIGQUIT() {
    printf("\nSignal sound times: %d", count);
    exit(0);
}

void handleSIGINT() {
    printf("\a");
    fflush(NULL);
    count++;
}

int main() {
    signal(SIGINT, &handleSIGINT);  // издает звуковой сигнал на вашем терминале каждый раз, когда вы вводите символ, на который у вас настроена посылка сигнала SIGINT
    signal(SIGQUIT, &handleSIGQUIT);  // При получении SIGQUIT, она должна вывести сообщение, говорящее, сколько раз прозвучал сигнал, и завершиться.
    while (1);
}