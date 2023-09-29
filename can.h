#ifndef _CAN_H_
#define _CAN_H_

#include <stdint.h>

#define CAN_SPEED_100K
#define CAN_SPEED_250K
#define CAN_SPEED_1000K
#define CAN_RB_LENGTH   128
#define CAN_RB_MASK     (CAN_RB_LENGTH - 1)

typedef enum{
 CAN_RB_OK    = 0x01,
 CAN_RB_FULL  = 0x02,
 CAN_RB_EMPTY = 0x03, 
} can_rb_enum;

typedef struct {
    uint32_t id;    
    uint8_t  data[8];
    uint32_t dlc : 4;
    uint32_t ext : 1;
    uint32_t rtr : 1;
    uint64_t ts;
} can_msg_struct;

typedef struct {
 can_msg_struct buffer[CAN_RB_LENGTH]; // message buffer
 uint32_t idx_in;                       // index to last writing
 uint32_t idx_out;                      // index to last reading
} can_rb_struct;

can_rb_enum can_rb_init(can_rb_struct *pbuf);
can_rb_enum can_rb_write(can_rb_struct *pbuf, can_msg_struct *pmsg);
can_rb_enum can_rb_read(can_rb_struct *pbuf, can_msg_struct *pmsg);

void can_init(uint32_t baudrate);
void can_set_filter(uint8_t number, uint32_t filter, uint32_t mask);
can_rb_enum can_read(can_msg_struct *msg);
can_rb_enum can_write(can_msg_struct *msg);

#endif