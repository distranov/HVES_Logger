#ifndef _CANLOG_H_
#define _CANLOG_H_

#include "can.h"

void canlog_msg(can_msg_struct *msg);
void canlog_str(can_msg_struct *msg, char *str);

#endif