#ifndef _CANDATA_H_
#define _CANDATA_H_

#include <stdint.h>

#include "can.h"

#define CANDATA_ID_SIZE sizeof(candata_id)/sizeof(candata_id[0])

const uint32_t candata_id[] = { 0x0C1BF3EF, 0x18FEF1EF,                          // EV 
        0x0CF090F3, 0x0CF091F3, 0x0CF092F3, 0x0CF093F3, 0x0CF094F3, 0x0CF095F3,  // Battery
        0x0CF0A0F3, 0x0CF10AF3, 0x0CF10BF3, 0x0CF10CF3, 0x0CFB8AF3, 0x0CF096F3, 
        0x0CF036F3, 0x18FECAF3, 0x18FFF0F3, 0x18F1093A,
        0x0CF19110, 0x0CF19210, 0x0CF19310, 0x0CF19410, 0x0CF19510, 0x0CF19610,  // String1
        0x0CF19810, 0x0CF19B10, 0x0CF19C10, 0x0CF19D10, 0x0CF19E10, 0x0CF19710,
        0x0CF19010, 0x0C2A10F3, 
        0x0CF1A020, 0x0CF1A120, 0x0CF1A220, 0x0CF1A320, 0x0CF1A420, 0x0CF1A520,  // String2
        0x0CF1A720, 0x0CF1AA20, 0x0CF1AB20, 0x0CF1AC20, 0x0CF1AD20, 0x0CF1A620,
        0x0CF19F20, 0x0C2B20F3,
};

typedef struct {
    uint64_t datetime;
    uint64_t bat[CANDATA_ID_SIZE];
    uint64_t sma[2][14];
    uint64_t cell[2][14][12];    
} candata_struct;

void candata_msg(can_msg_struct *msg);
void candata_parser(can_msg_struct *msg, candata_struct *data);

#endif