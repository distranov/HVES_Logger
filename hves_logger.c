#include <stdio.h>
#include <unistd.h>

#include "time_ms.h"

int main() {
    time_ms_struct tm;
    for(uint32_t i = 0; i < 100; i++) {
        time_ms_get_datetime(&tm);
        printf("%02d:%02d:%02d.%03d %02d-%02d-%04d \n",
            tm.hour,
            tm.minutes,
            tm.seconds,
            tm.msec,
            tm.day,
            tm.month,
            tm.year
            );
        usleep(1000);
    }
    printf("hello\n");
    return 0;
}
