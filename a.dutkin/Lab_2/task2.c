#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>

extern char* tzname[];

int main()
{
    char *some_timezone = "TZ=US/Pacific";
		putenv(some_timezone);
    time_t hms;
    time(&hms);
    printf("%s", ctime(&hms));
    struct tm *t = localtime(&hms);
    printf("%d/%d/%02d %d:%02d %s\n", ++t->tm_mon, t->tm_mday, t->tm_year % 100, t->tm_hour, t->tm_min, tzname[t->tm_isdst]);
    return 0;
}

