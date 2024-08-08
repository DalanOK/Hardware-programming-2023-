#include "file_system.h"
#include "../kernel/kernel.h"
#include "../drivers/keyboard/keyboard.h"
#include "../strComands/str.h"
#include "../keyboardRules/keyboardRules.h"
#include "../messageControler/messageControler.h"

#define MAX_FILES 10
#define MAX_FILE_SIZE 2000

struct File {
    char name[20];
    char content[MAX_FILE_SIZE];
    unsigned int size;
    bool in_use;
};

char currentFileName[];

struct File file_system[MAX_FILES];

void create_file(char* filename) {
    for (int i = 0; i < MAX_FILES; ++i) {
        if (my_strcmp(file_system[i].name, filename) == 0 && file_system[i].in_use) {
            write_message("Error: File all ready exist", 0x4);
            return;
        }
    }
    for (int i = 0; i < MAX_FILES; ++i) {
        if (!file_system[i].in_use) {
            my_strcpy(file_system[i].name, filename);
            file_system[i].size = 0;
            file_system[i].in_use = true;
            write_message("File created successfully", 0x2);
            return;
        }
    }
    write_message("Error: Maximum number of files reached", 0x4);
}
void edit_file(char* filename) {
    my_strcpy(currentFileName, filename);
    keyboard_set_handler(key_handler_edit_file);
}
void write_to_file(char* filename, char* content) {
    if (my_strlen(content) > MAX_FILE_SIZE){
        write_message("Error: File too big", 0x4);
        return;
    }
    else {
        for (int i = 0; i < MAX_FILES; ++i) {
            if (file_system[i].in_use && my_strcmp(file_system[i].name, filename) == 0) {
                my_strcpy(file_system[i].content, content);
                file_system[i].size = my_strlen(content);
                write_message("Content written to file", 0x2);
                return;
            }
        }
    }
    write_message("Error: File not found", 0x4);
}
void read_file(char* filename) {
    for (int i = 0; i < MAX_FILES; ++i) {
        if (file_system[i].in_use && my_strcmp(file_system[i].name, filename) == 0) {
            write_message(file_system[i].content, 0xd);
            return;
        }
    }
    write_message("Error: File not found", 0x4);
}
void delete_file(char* filename) {
    for (int i = 0; i < MAX_FILES; ++i) {
        if (file_system[i].in_use && my_strcmp(file_system[i].name, filename) == 0) {
            my_strcpy(file_system[i].content, "");
            file_system[i].in_use = false;
            write_message("File deleted successfully", 0x2);
            return;
        }
    }
    write_message("Error: File not found", 0x4);
}

void list_files() {
    write_message("List of files:", 0x2);
    for (int i = 0; i < MAX_FILES; ++i) {
        if (file_system[i].in_use) {
            write_message(file_system[i].name, 0x2);
        }
    }
}
