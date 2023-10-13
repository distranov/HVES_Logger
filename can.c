#include <linux/can.h>
#include <linux/can/raw.h>
#include <net/if.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "can.h"
#include "time_ms.h"

pthread_t thread;
pthread_mutex_t mtx;
can_rb_struct can_rx_buf;
can_rb_struct can_tx_buf;

volatile bool start;
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

    pthread_mutex_lock(&mtx);
    pbuf->buffer[next] = *pmsg;
    pbuf->idx_in = next;
    pthread_mutex_unlock(&mtx);

    return CAN_RB_OK;
}
//-----------------------------------------------------------------------------
can_rb_enum can_rb_read(can_rb_struct *pbuf, can_msg_struct *pmsg) {
    uint16_t next;

    if(pbuf->idx_in == pbuf->idx_out)
        return CAN_RB_EMPTY;
       
    next = (pbuf->idx_out + 1) & CAN_RB_MASK;
    
    *pmsg = pbuf->buffer[next];

    pthread_mutex_lock(&mtx);
    pbuf->idx_out = next;
    pthread_mutex_unlock(&mtx);

    return CAN_RB_OK;
}
//-----------------------------------------------------------------------------
void* thread_body(void* arg) {
    struct ifreq ifr;
    int can_desc;
    struct sockaddr_can addr;
    int nbytes;
    struct can_frame frame;
    can_msg_struct msg;

    can_desc = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    strcpy(ifr.ifr_name, "vcan0" );
    ioctl(can_desc, SIOCGIFINDEX, &ifr);

    memset(&addr, 0, sizeof(addr));
    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    bind(can_desc, (struct sockaddr *)&addr, sizeof(addr));

    while(start) {
        nbytes = read(can_desc, &frame, sizeof(struct can_frame));

        msg.id = frame.can_id & 0x1FFFFFFF;
        msg.dlc = frame.can_dlc;
        memcpy((void*)msg.data, (void*)frame.data, 8);
        //msg.ts = time_ms_get_datetime64();
        msg.ts = time_ms_get_ms();
        //printf("received in:%03d out:%03d\n ", can_rx_buf.idx_in, can_rx_buf.idx_out);
        can_rb_write(&can_rx_buf, &msg);
        //usleep(100);
    }    
    close(can_desc);

    return NULL;
}

//-----------------------------------------------------------------------------
void can_init(uint32_t baudrate)
{
    start = true;
    can_rb_init(&can_rx_buf);
    pthread_mutex_init(&mtx, NULL);
    pthread_create(&thread, NULL, thread_body, NULL);   
}

//-----------------------------------------------------------------------------
can_rb_enum can_read(can_msg_struct *pmsg) {
    return can_rb_read(&can_rx_buf, pmsg);
}
