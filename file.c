/*

*/
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>

#include "file.h"
#include "time_ms.h"


#define PATH "/media/sdcard/hves_archive"
#define PERMS 0666                     // RW для собственника, группы и ост-х 

//-----------------------------------------------------------------------------
bool file_is_new_name(char *filename) {
    static uint64_t prev_hour = 0;
    time_ms_union t;
    char path[80];
    struct stat st = {0};
    
    t.u64 = time_ms_get_datetime64();

    if(t.s.minutes != prev_hour) {
        prev_hour = t.s.minutes;
        // проверяем и создаем папку дня          
        if(stat(PATH, &st) == -1) { 
            if(mkdir(PATH, PERMS) != 0) exit(1);
        }
        sprintf(path, "%s/%02d-%02d-%02d", PATH, t.s.day, t.s.month, t.s.year);
        if(stat(path, &st) == -1) { 
            if(mkdir(path, PERMS) != 0) exit(2);
        }    
        sprintf(filename, "%s/%02d_%02d.cxe", path, t.s.hour, t.s.minutes);    
        return true;
    }    
    return false;
}

//-----------------------------------------------------------------------------
void file_write(const char *str) {
    char filename[100];
    static FILE *fp = NULL;

    if(file_is_new_name(filename)) {    
        if(fp) fclose(fp);                  
        creat(filename, PERMS);         
        fp = fopen(filename, "a");
        if(fp == NULL) {
            exit(3); 
        }        
    }

    if(fp) {
        fwrite(str, 1, strlen(str), fp);       
    }  
}
