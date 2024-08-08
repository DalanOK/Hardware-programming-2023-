#ifndef MESSAGE_CONTROLER_H
#define MESSAGE_CONTROLER_H

void write_message(char* message, unsigned char color);
void write_to_buffer(char key, char* message_buffer, char* command);
void write_message_from_buffer(char* message, unsigned char color);

#endif
