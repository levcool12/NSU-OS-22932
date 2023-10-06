#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main()
{
    time_t now;
    setenv("TZ", "US/Pacific", 1);
    tzset();
    (void) time(&now);
    printf("%s", ctime(&now));
    return 0;
}