#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "candata.h"
#include "file.h"

//-----------------------------------------------------------------------------
void candata_msg(can_msg_struct *msg) {
    static FILE *fp = NULL;
    static uint32_t prev_hours = 24;
    static uint32_t prev_sec = 0;
    char filename[200];
    char str[100];
    uint32_t t = 0;
    int ret;
    candata_struct data;

    candata_parser(msg, &data); 
    t = msg->ts/1000;
    if(prev_sec == t) return;
    prev_sec = t;

    t = msg->ts/1000/3600 % 24;
    if(prev_hours != t) { 
        prev_hours = t;
        file_new_name(filename, FILE_TYPE_CXE);
        if(fp) fclose(fp);                  
        creat(filename, 0666);         
        fp = fopen(filename, "a");
        if(fp == NULL) exit(3); 
        ret = system("./hves_cleaner.bin /media/sdcard/hves_log *.log 1 100000 &");
    }
    
    data.datetime = msg->ts;
    if(fp) fwrite((void*)&data, 1, sizeof(data), fp);  
    
}
//-----------------------------------------------------------------------------
void candata_parser(can_msg_struct *msg, candata_struct *data) {
   
    uint64_t data64;

    memcpy(&data64, msg->data, 8);

    if((msg->id & 0xFFFF00) == 0xFFDC00) {
        if((msg->id & 0xFF) == 0x10) 
            data->cell[0][msg->data[0] - 1][msg->data[1] - 1] = data64;
        if((msg->id & 0xFF) == 0x20)
            data->cell[1][msg->data[0] - 1][msg->data[1] - 1] = data64;           
        return;
    }

    if((msg->id & 0xFFFF00) == 0xFFDD00) {
        if((msg->id & 0xFF) == 0x10)
            data->sma[0][msg->data[0] - 1] = data64;
        if((msg->id & 0xFF) == 0x20)
            data->sma[1][msg->data[0] - 1] = data64;           
        return;
    }

    for(uint32_t i = 0; i < CANDATA_ID_SIZE; i++) {
        if(msg->id == candata_id[i]) data->bat[i] = data64;
    }
}
