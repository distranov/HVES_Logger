#include "can.h"


//-----------------------------------------------------------------------------
can_rb_enum can_rb_init(can_rb_struct *pbuf) {
    pbuf->idx_in  = 0;
    pbuf->idx_out = 0;
    return CAN_RB_EMPTY;
}
//-----------------------------------------------------------------------------
can_rb_enum can_rb_write(can_rb_struct *pbuf, can_msg_struct *pmsg) {
    uint16_t next;
   
    next = (pbuf->idx_in + 1) & CAN_RB_MASK;

    if(next == pbuf->idx_out)
        return CAN_RB_FULL;
   
    pbuf->buffer[next] = *pmsg;
    pbuf->idx_in = next;
    return CAN_RB_OK;
}
//-----------------------------------------------------------------------------
can_rb_enum can_rb_read(can_rb_struct *pbuf, can_msg_struct *pmsg) {
    uint16_t next;

    if(pbuf->idx_in == pbuf->idx_out)
        return CAN_RB_EMPTY;
       
    next = (pbuf->idx_out + 1) & CAN_RB_MASK;
    
    *pmsg = pbuf->buffer[next];
    pbuf->idx_out = next;
    return CAN_RB_OK;
}
