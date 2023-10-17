#include <stdio.h>
#include <time.h>

int main() {
    putenv("TZ=PST8PDT");
    time_t current_time = time(NULL);
    struct tm* local_time = localtime(&current_time);
    char buff[50];
    strftime(buff, sizeof(buff), "%Y-%m-%d %H:%M:%S", local_time);
    printf(" %s\n", buff);

    return 0;
}