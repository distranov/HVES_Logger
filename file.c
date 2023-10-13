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

//-----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
void file_new_name(char *filename, file_type_enum filetype) {
    time_ms_union t;
    struct stat st = {0};
    char path[200] = {0};
    
    t.u64 = time_ms_get_datetime64();

    if(filetype == FILE_TYPE_CXE) {
        if(stat(FILE_PATH_CXE, &st) == -1) { if(mkdir(FILE_PATH_CXE, PERMS) != 0) exit(1); }
        sprintf(path, "%s/%02d-%02d-%02d", FILE_PATH_CXE, t.s.day, t.s.month, t.s.year);
        if(stat(path, &st) == -1) { if(mkdir(path, PERMS) != 0) exit(2); }  
        sprintf(filename, "%s/%02d_%02d.cxe", path, t.s.hour, t.s.minutes);          
    }
    else {
        if(stat(FILE_PATH_LOG, &st) == -1) { if(mkdir(FILE_PATH_LOG, PERMS) != 0) exit(1); }
        sprintf(path, "%s/%02d-%02d-%02d", FILE_PATH_LOG, t.s.day, t.s.month, t.s.year);
        if(stat(path, &st) == -1) { if(mkdir(path, PERMS) != 0) exit(2); }  
        sprintf(filename, "%s/%02d_%02d.log", path, t.s.hour, t.s.minutes);  
    }
    printf("%s\n", filename);
    return;
}