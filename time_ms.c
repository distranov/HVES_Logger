#include <sys/time.h>
#include <time.h>
#include "time_ms.h"
//-----------------------------------------------------------------------------
int time_ms_get_datetime(time_ms_struct *td) {
    int res;
    struct timeval tv;
    struct tm      *tm;  

    res = gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec); // gmtime for UTC
    
    td->year = tm->tm_year + 1900;
    td->month = tm->tm_mon + 1;
    td->day = tm->tm_mday;
    td->hour = tm->tm_hour;
    td->minutes = tm->tm_min;
    td->seconds = tm->tm_sec;
    td->msec = (int) (tv.tv_usec/1000);

    return res;
}
