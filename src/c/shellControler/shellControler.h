#ifndef SHELL_CONTROLLER_H
#define SHELL_CONTROLLER_H

extern unsigned int line;
extern unsigned int screen;

unsigned short get_cursor();
void saveScreen();
void loadScreen();
void scroll();
void clear_shell();
void switchLine();
void needToScrollCheck();
void clear_message_buffer(char* buffer, int length);
unsigned int getLine();

#endif 