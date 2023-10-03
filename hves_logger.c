#include <stdio.h>
#include <unistd.h>

#include "can.h"
#include "file.h"
#include "time_ms.h"

#define HVES_LOGGER_VERSION 103

int main() {
    can_msg_struct msg;
    time_ms_union  ts;   
    char s[80];

    can_init(250000);

    while(1) {
        while(can_read(&msg) == CAN_RB_OK) {
            ts.u64 = msg.ts;
            sprintf(s, "%08x %01d %02x %02x %02x %02x %02x %02x %02x %02x %02d:%02d:%02d.%03d\n",
                    msg.id,
                    msg.dlc,
                    msg.data[0], msg.data[1], msg.data[2], msg.data[3], 
                    msg.data[4], msg.data[5], msg.data[6], msg.data[7],
                    ts.s.hour, ts.s.minutes, ts.s.seconds, ts.s.msec
                   );       
            //printf("%s",s);
            file_write(s);
        }
        usleep(1000);
    }
    return 0;
}



