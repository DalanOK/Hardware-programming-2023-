#include "../fileSystem/file_system.h"
#include "../strComands/str.h"
#include "../shellControler/shellControler.h"
#include "../drivers/keyboard/keyboard.h"
#include "../kernel/kernel.h"
#include "../messageControler/messageControler.h"
#include "keyboardRules.h"

void key_handler(struct keyboard_event event) {
    static char message_buffer[2000];
    static char command[2000];
    static char command_argument[2000];
    static bool hasArgument = false;
    if (event.type == EVENT_KEY_PRESSED) {
        if (event.key_character == '\n') {
            put_cursor(get_cursor() + 80 - my_strlen(message_buffer));
            switchOnlyLine();
            comand_manager(command, command_argument);
            clear_message_buffer(command, my_strlen(command));
            clear_message_buffer(command_argument, my_strlen(command_argument));
            clear_message_buffer(message_buffer, my_strlen(message_buffer));
            hasArgument = false;
        }
        else {
            if (event.key_character == ' ') {
                hasArgument = true;
            }
            if (hasArgument == true) {
                write_to_buffer(event.key_character, message_buffer, command_argument);
            }
            else {
                write_to_buffer(event.key_character, message_buffer, command);
            }
        }
    }
}
void key_handler_edit_file(struct keyboard_event event) {
    static char message_buffer[2000];
    static char command[2000];
    if (event.type == EVENT_KEY_PRESSED) {
        if (event.key_character == '\n') {
            /*
            while (my_strlen(message_buffer) % 80 != 0) {
                message_buffer[my_strlen(message_buffer) + 1] = ' ';
            }
            */
        }
        else if (event.key_character == '\t') {
            write_to_file(currentFileName, message_buffer);
            clear_message_buffer(message_buffer, my_strlen(message_buffer));
            clear_message_buffer(command, my_strlen(command));
            loadScreen();

        }
        else {
            write_to_buffer(event.key_character, message_buffer, command);
        }
    }
}
void clear_message_buffer(char* buffer, int length) {
    for (int i = 0; i < length; i++) {
        buffer[i] = '\0';
    }
}
void key_handler_sleep(struct keyboard_event event) {
    if (event.type == EVENT_KEY_PRESSED) {
        if (event.key_character == '\t') {
            screen = 0;
            loadScreen();
        }
    }
}