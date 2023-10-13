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
        ret = system("./hves_cleaner.bin /media/sdcard/hves_log *.log 1 168 &");
    }
    
    data.hh = msg->ts/1000/3600 % 24;
    data.mm = msg->ts/1000/60 % 60;
    data.ss = msg->ts/1000 % 60;
    //printf("%02d:%02d:%02d\n", data.hh, data.mm, data.ss);
    if(fp) fwrite((void*)&data, 1, sizeof(data), fp);  
    
}
//-----------------------------------------------------------------------------
void candata_parser(can_msg_struct *msg, candata_struct *data) {



}
