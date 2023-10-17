#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>

void foo(int y, int m, int d, int h, int min, int s);
int main()
{
    time_t tmi;
    struct tm* utcTime;

    time(&tmi);
    utcTime = gmtime(&tmi);
    printf("\n");
    printf("UTC Time: %2d:%02d:%02d\n", (utcTime->tm_hour) % 24, utcTime->tm_min, utcTime->tm_sec);
    if (utcTime->tm_hour - 8 < 0) 
    {
        foo(utcTime->tm_year + 1900, utcTime->tm_mon + 1, utcTime->tm_mday, (utcTime->tm_hour - 8) % 24, utcTime->tm_min, utcTime->tm_sec);
        return 0;
    }
    printf("In California %d year %d month %d day\n", utcTime->tm_year + 1900, utcTime->tm_mon + 1, utcTime->tm_mday);
    printf("Time in California: %2d:%02d:%02d\n", (utcTime->tm_hour - 8) % 24, utcTime->tm_min, utcTime->tm_sec);

    return (0);
}

void foo(int y, int m, int d, int h, int min, int s) {
    int y1=0, m1=0, d1=0, h1=0, min1=0;
    h1 = 24 + h;
    int arr[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (d - 1 < 0) {
        if (m - 1 < 0) {
            d1 = arr[11];
            y1--;

        }
        if (m - 1 >= 0) {
            d1 = arr[m];
            y1 = y;
        }

    }
    if (d - 1 >= 0) {
        d1 = d;
        y1 = y;
        m1 = m;
     }

    printf("In California %d year %d month %d day\n", y1, m1, d1);
    printf("Time in California: %2d:%02d:%02d\n", h1, min, s);
    return;
}
