#include "sleep.h";
#include "../../messageControler/messageControler.h"
#include "../shellControler.h"
#include "../../kernel/kernel.h";
#include "../../keyboardRules/keyboardRules.h";
unsigned int directionY = 160;
unsigned int directionX = 0;
bool directionYswitch = false;
bool directionXswitch = false;
void clearConsoleForSleep() {
    char* framebuffer = (char*)0xb8000;
    for (int i = 0; i < 80 * 25; i++) {
        *framebuffer = ' ';
        *(framebuffer + 1) = 0x0;
        framebuffer += 2;
    }
}
void sleep() {
    saveScreen();
    clearConsoleForSleep();
    keyboard_set_handler(key_handler_sleep);
    unsigned char color = 0x2;


    print(" (((((((((( ", color, directionY, directionX);
    print("(|(*)||(*)|)", color, directionY + (160 * 2), directionX);
    print("|    ||    |", color, directionY + (160 * 3), directionX);
    print("| (_____)  |", color, directionY + (160 * 4), directionX);

    if (directionY == (160 * 19)) {
        directionY -= 160;
        directionYswitch = true;
    }
    else if (directionY == 160) {
        directionY += 160;
        directionYswitch = false;
    }
    else if (!directionYswitch) {
        directionY += 160;
    }
    else {
        directionY -= 160;
    }

    if (directionX == 68 * 2) {
        directionX--;
        directionXswitch = true;
    }
    else if (directionX == 10) {
        directionX++;
        directionXswitch = false;
    }
    else if (!directionXswitch) {
        directionX++;
    }
    else {
        directionX--;
    }
}