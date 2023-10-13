#ifndef _FILE_H_
#define _FILE_H_

#define FILE_PATH_LOG "/media/sdcard/hves_log"
#define FILE_PATH_CXE "/media/sdcard/hves_data"
#define PERMS 0666                     // RW для собственника, группы и ост-х 

typedef enum {
    FILE_TYPE_CXE = 1,
    FILE_TYPE_LOG = 2    
 } file_type_enum;

void file_new_name(char *filename, file_type_enum filetype);

#endif

