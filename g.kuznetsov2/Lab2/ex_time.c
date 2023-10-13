#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    time_t curTime;
    struct tm *date;
    time(&curTime);             //put milliseconds time in var
    printf("UTC %s", asctime(gmtime(&curTime)));
    date = gmtime(&curTime);    //put time in comfort struct with fields
    date->tm_hour -= 8;
    if((date->tm_mon < 11 && date->tm_mon > 3) || (date->tm_mon == 1 && date-> tm_mday < 15) || (date->tm_mon == 3 && date->tm_mday > 12)) date->tm_hour++;
    if (date->tm_hour < 0) {
        date->tm_hour += 24;
        date->tm_mday-= 1;
    }
    printf("Sun beautiful place date and time are %s", asctime(date));
    return 0;
}
