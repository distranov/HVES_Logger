#ifndef _CANDATA_H_
#define _CANDATA_H_

#include "can.h"

typedef struct {

} candata_struct;

void candata_msg(can_msg_struct *msg);
void candata_parser(can_msg_struct *msg, candata_struct *data);

#endif