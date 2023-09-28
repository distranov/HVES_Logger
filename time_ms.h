

#ifndef _TIME_MS_H_
#define _TIME_MS_H_

#include <stdint.h>

typedef struct {
    uint64_t year    : 16;
    uint64_t month   : 4;
    uint64_t day     : 5;
    uint64_t hour    : 5;
    uint64_t minutes : 6;
    uint64_t seconds : 6;
    uint64_t msec    : 10;
} time_ms_struct;

int time_ms_get_datetime(time_ms_struct *td);

#endif
