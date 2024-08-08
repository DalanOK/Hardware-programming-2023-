#include "shellControler.h"
#include "../keyboardRules/keyboardRules.h"

unsigned int line = 0;
unsigned int savedLine = 0;
unsigned int savedCursPos = 0;
unsigned int screen = 0;

unsigned short get_cursor() {
    unsigned short position = 0;
    out(0x3D4, 14);
    position = in(0x3D5) << 8;
    out(0x3D4, 15);
    position |= in(0x3D5);

    return position;
}
void saveScreen() {
    //mainScreen = false;
    savedLine = line;
    savedCursPos = get_cursor();
    char* framebuffer = (char*)0xb8000;
    char* source = (char*)0xb8000;
    char* target = (char*)0xb11000;

    for (int i = 0; i < (24 * 80 * 2); i++) {
        *target = *source;
        *(target + 1) = *(source + 1);
        source++;
        target++;
    }
    for (int i = 0; i < 80 * 24 * 2; i++) {
        *framebuffer = ' ';
        *(framebuffer + 1) = 0x0;
        framebuffer += 2;
    }
    line = 0;
    put_cursor(1);
}
void loadScreen() {
    screen = 0;
    char* framebuffer = (char*)0xb8000;
    char* source = (char*)0xb11000;
    char* target = (char*)0xb8000;

    for (int i = 0; i < 80 * 24 * 2; i++) {
        *framebuffer = ' ';
        *(framebuffer + 1) = 0x0;
        framebuffer += 2;
    }

    for (int i = 0; i < (24 * 80 * 2); i++) {
        *target = *source;
        *(target + 1) = *(source + 1);
        source++;
        target++;
    }
    line = savedLine;
    put_cursor(savedCursPos);
    keyboard_set_handler(key_handler);
}
void scroll() {
    char* framebuffer = (char*)0xb8000;
    for (int i = 0; i < 80; i++) {
        *framebuffer = ' ';
        *(framebuffer + 1) = 0x0;
        framebuffer += 2;
    }
    char* source = (char*)0xb8000 + 80 * 2;
    char* target = (char*)0xb8000;

    for (int i = 0; i < (24 * 80 * 2); i++) {
        *target = *source;
        *(target + 1) = *(source + 1);
        source++;
        target++;
    }
    line -= 160;
    put_cursor(get_cursor() - 80);
}
void clear_shell() {
    char* framebuffer = (char*)0xb8000;
    int counter = 0;
    while (counter < (80 * 25)) {
        *framebuffer = ' ';
        *(framebuffer + 1) = 0x2;
        framebuffer += 2;
        counter++;
    }
    put_cursor(0);
    line = 0;
}
void switchLine() {
    line += 160;
    put_cursor(get_cursor() + 80);
}
void switchOnlyLine() {
    line += 160;
}
void needToScrollCheck() {
    if (line >= 23 * 160) {
        scroll();
    }
}
unsigned int getLine() {
    return line;
}