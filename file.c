/*

*/


#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "file.h"
#include "time_ms.h"


static FILE *fp;

// #define PATH "/media/sdcard/hves_archive"
//-----------------------------------------------------------------------------
bool file_is_new_name(char *filename) {
    static uint64_t prev_hour = 0;
    time_ms_union t;
    
    t.u64 = time_ms_get_datetime64();   

    if(t.s.minutes != prev_hour) {
        prev_hour = t.s.minutes;
        // проверяем и создаем папку дня  
         

        sprintf(filename, "/media/sdcard/hves_archive/%02d-%02d-%02d/%02d_%02d.cxe",
            t.s.day, t.s.month, t.s.year, t.s.hour, t.s.minutes
        );        
        return true;
    }    
    return false;
   
   

    

// в зависисмости от текущей даты формируем дополнительные папки year-month-day

// формируем имя файла для создания или добавления данных



}


//-----------------------------------------------------------------------------
void file_write(const char *file_name) {
fp = fopen(file_name, "a");

}
