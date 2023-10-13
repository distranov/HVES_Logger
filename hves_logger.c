#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>

#include "can.h"
#include "candata.h"
#include "canlog.h"

#include "file.h"
#include "time_ms.h"

#define HVES_LOGGER_VERSION 105

//-----------------------------------------------------------------------------
void led_10ms() {
    static int led_timer = 0;
    static bool led_on;
    int ret;
    if(led_timer++ < 10) return;
    led_timer = 0;
    led_on = !led_on;
    if(led_on) ret = system("echo 1 > /sys/class/leds/gledg/brightness");
    else ret = system("echo 0 > /sys/class/leds/gledg/brightness");
}
//-----------------------------------------------------------------------------
int main() {
    can_msg_struct msg;
    
    can_init(250000);  

    while(1) {
        while(can_read(&msg) == CAN_RB_OK) {
            canlog_msg(&msg);
            candata_msg(&msg);
            
        }
        usleep(10000);
        led_10ms();
    }
    return 0;
}



