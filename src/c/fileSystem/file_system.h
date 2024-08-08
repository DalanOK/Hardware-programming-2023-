#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H


#define MAX_FILES 10
#define MAX_FILE_SIZE 2000

extern char currentFileName[];

extern unsigned int my_strlen(const char* str);
extern void my_strcpy(char* dest, const char* src);
extern void create_file(char* filename);
extern void write_to_file(char* filename, char* content);
extern void read_file(char* filename);
extern void delete_file(char* filename);
extern void list_files();

#endif  

