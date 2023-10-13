#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
//    time_t t = time(NULL);
//    printf("UTC:       %s", asctime(gmtime(&t)));
//    printf("local:     %s", asctime(localtime(&t)));
//    // POSIX-specific
//    putenv("TZ=Asia/Japan");
//    printf("Singapore: %s", asctime(localtime(&t)));
    time_t curTime;
    struct tm *date;
    time(&curTime);             //put milliseconds time in var
    printf("UTC %s", asctime(gmtime(&curTime)));
    date = gmtime(&curTime);    //put time in comfort struct with fields
//    printf("minutes %d hours %d mday %d month %d year %d isSummer %d\n", date->tm_min, date->tm_hour, date->tm_mday, date->tm_mon, date->tm_year, date->tm_isdst);
//    printf("minutes %d hours %d mday %d month %d year %d  isSummer %d\n", date->tm_min, date->tm_hour, date->tm_mday, date->tm_mon, date->tm_year, date->tm_isdst);
    date->tm_hour -= 8;
    if((date->tm_mon < 11 && date->tm_mon > 3) || (date->tm_mon == 1 && date-> tm_mday < 15) || (date->tm_mon == 3 && date->tm_mday > 12)) date->tm_hour++;
    if (date->tm_hour < 0) {
        date->tm_hour += 24;
        date->tm_mday-= 1;
    }
//    printf("minutes %d hours %d mday %d month %d year %d  isSummer %d\n", date->tm_min, date->tm_hour, date->tm_mday, date->tm_mon, date->tm_year, date->tm_isdst);
    printf("Sun beautiful place date and time are %s", asctime(date));
//    printf("Sun beautiful place date and time are %s", asctime(gmtime(&curTime)));
    return 0;
}
