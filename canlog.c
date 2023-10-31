#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "canlog.h"
#include "file.h"

//-----------------------------------------------------------------------------
void canlog_msg(can_msg_struct *msg) {    
    static FILE *fp = NULL;
    static uint32_t prev_hours = 24;
    char filename[200];
    char str[100];
    uint32_t t = 0;
    int ret;

    t = msg->ts/1000/3600 % 24;
    if(prev_hours != t) { 
        prev_hours = t;
        file_new_name(filename, FILE_TYPE_LOG);
        if(fp) fclose(fp);                  
        creat(filename, 0666);         
        fp = fopen(filename, "a");
        if(fp == NULL) exit(3); 
        ret = system("./hves_cleaner.bin /media/sdcard/hves_log *.log 1 168 &");
    }
    canlog_str(msg, str); 
    if(fp) fwrite(str, 1, strlen(str), fp);      
}
//-----------------------------------------------------------------------------
void canlog_str(can_msg_struct *msg, char *str) {
    sprintf(str, "%08x %01d %02x %02x %02x %02x %02x %02x %02x %02x %016lx\n",
        msg->id,
        msg->dlc,
        msg->data[0], msg->data[1], msg->data[2], msg->data[3], 
        msg->data[4], msg->data[5], msg->data[6], msg->data[7],
        msg->ts
    );       
}