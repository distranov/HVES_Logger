#include <sys/time.h>
#include <time.h>
#include "time_ms.h"

//-----------------------------------------------------------------------------
uint64_t time_ms_get_datetime64(void) {
    time_ms_union  td;    
    struct timeval tv;
    struct tm      *tm;  

    gettimeofday(&tv, NULL);
    tm = localtime(&tv.tv_sec); // gmtime for UTC
    
    td.s.year = tm->tm_year + 1900;
    td.s.month = tm->tm_mon + 1;
    td.s.day = tm->tm_mday;
    td.s.hour = tm->tm_hour;
    td.s.minutes = tm->tm_min;
    td.s.seconds = tm->tm_sec;
    td.s.msec = (int) (tv.tv_usec/1000);

    return td.u64;
}
//-----------------------------------------------------------------------------
uint64_t time_ms_get_ms(void) {
    uint64_t res;
    struct timeval tv;

    gettimeofday(&tv, NULL);
    res = (uint64_t)tv.tv_sec*1000 + tv.tv_usec/1000;

    //res = 0x1234567890123456;
    return res; 
}