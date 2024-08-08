#include "messageControler.h"
#include "../strComands/str.h"
#include "../shellControler/shellControler.h"

void write_to_buffer(char key, char* message_buffer, char* command) {
    char* framebuffer = (char*)0xb8000 + getLine();
    if (key == '\b' && my_strlen(message_buffer) > 0) {
        message_buffer[my_strlen(message_buffer) - 1] = '\0';
        command[my_strlen(command) - 1] = '\0';

        *(framebuffer + (my_strlen(message_buffer) * 2)) = ' ';
        put_cursor(get_cursor() - 1);
    }
    else {
        message_buffer[my_strlen(message_buffer)] = key;
        command[my_strlen(command)] = key;
        write_message_from_buffer(message_buffer, 0x2);
        put_cursor(get_cursor() + 1);
    }
}

void write_message_from_buffer(char* message, unsigned char color) {
    char* framebuffer = (char*)0xb8000 + getLine();
    while (*message != '\0') {
        *framebuffer = *message;
        *(framebuffer + 1) = color;
        framebuffer += 2;
        message++;
    }
}
void write_message(char* message, unsigned char color) {
    char* framebuffer = (char*)0xb8000 + getLine();
    while (*message != '\0') {
        *framebuffer = *message;
        *(framebuffer + 1) = color;
        framebuffer += 2;
        message++;
    }
    needToScrollCheck();
    switchLine();
}
void print(char* message, unsigned char color, unsigned int directionY, unsigned int directionX) {
    char* framebuffer = (char*)0xb8000 + directionY + directionX;
    while (*message != '\0') {
        *framebuffer = *message;
        *(framebuffer + 1) = color;
        framebuffer += 2;
        message++;
    }
}