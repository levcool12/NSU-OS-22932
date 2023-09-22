#include <sys/types.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
extern char* tzname[];

int main()
{
	char* timezone = "TZ=US/Pacific";
	time_t hms;
	struct tm* t;
	putenv(timezone);
	time(&hms);
	printf("%s", ctime(&hms));
	t = localtime(&hms);
	printf("%d/%d/%02d %d:%02d %s\n",
		++t->tm_mon, t->tm_mday,
		t->tm_year%100, t->tm_hour,
		t->tm_min, tzname[t->tm_isdst]);
	return 0;
}

