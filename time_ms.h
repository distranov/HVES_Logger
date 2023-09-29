

#ifndef _TIME_MS_H_
#define _TIME_MS_H_

#include <stdint.h>

typedef union {
    uint64_t u64;
    struct {
        uint64_t year    : 16;
        uint64_t month   : 4;
        uint64_t day     : 5;
        uint64_t hour    : 5;
        uint64_t minutes : 6;
        uint64_t seconds : 6;
        uint64_t msec    : 10;
    } s;
} time_ms_union;

uint64_t time_ms_get_datetime64(void);

#endif
