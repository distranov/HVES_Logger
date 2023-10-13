#ifndef _CANDATA_H_
#define _CANDATA_H_

#include <stdint.h>

#include "can.h"

typedef struct {
    uint8_t hh;
    uint8_t mm;
    uint8_t ss;

} candata_struct;

void candata_msg(can_msg_struct *msg);
void candata_parser(can_msg_struct *msg, candata_struct *data);

#endif