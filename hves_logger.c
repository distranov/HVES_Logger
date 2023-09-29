#include <stdio.h>
#include <unistd.h>

#include "can.h"
#include "file.h"
#include "time_ms.h"

#define HVES_LOGGER_VERSION 101

int main() {
    can_msg_struct msg;
    time_ms_union  ts;
    char filename[80];
   
    printf("HVES_LOGGER ver %1.2f is start\n", HVES_LOGGER_VERSION/100.0);
    
    can_init(250000);

    while(1) {
        
        if(file_is_new_name(filename)) 
            printf("%s",filename);
        else
            printf("old name");    
        printf("\n");
      
        while(can_read(&msg) == CAN_RB_OK) {
            ts.u64 = msg.ts;
            printf("%08x %01d %02x %02x %02x %02x %02x %02x %02x %02x ",
                            msg.id,
                            msg.dlc,
                            msg.data[0], msg.data[1], msg.data[2], msg.data[3], 
                            msg.data[4], msg.data[5], msg.data[6], msg.data[7]
                            );
            printf("%02d:%02d:%02d.%03d\n", ts.s.hour, ts.s.minutes, ts.s.seconds, ts.s.msec);            
        }
        
            
        


        sleep(1);

        }
    return 0;

}



