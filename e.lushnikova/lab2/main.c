#define _CRT_SECURE_NO_WARNINGS
#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

extern char* tzname[];

int main()
{
    time_t now;
    struct tm* sp;
    char buf[256];
    setenv("TZ", "PST8PDT", 1);
    time(&now);
    printf("%s", ctime(&now));
    sp = localtime(&now);
    strftime(buf, sizeof(buf), "%m/%d/%y %I:%M %p %Z", sp);
    printf("%s\n", buf);

    return 0;
}