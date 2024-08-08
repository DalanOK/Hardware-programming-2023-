#include "kernel/kernel.h"
#include "drivers/keyboard/keyboard.h"
#include "drivers/timer/timer.h"
#include "drivers/serial_port/serial_port.h"
#include "fileSystem/file_system.h"
#include "strComands/str.h"
#include "shellControler/shellControler.h"
#include "keyboardRules/keyboardRules.h"
#include "messageControler/messageControler.h"
#include "shellControler/sleep/sleep.h"

void exception_handler(u32 interrupt, u32 error, char *message) {
    serial_log(LOG_ERROR, message);
}

void init_kernel() {
    init_gdt();
    init_idt();
    init_exception_handlers();
    init_interrupt_handlers();
    register_timer_interrupt_handler();
    register_keyboard_interrupt_handler();
    configure_default_serial_port();
    set_exception_handler(exception_handler);
    enable_interrupts();
}
//static unsigned int screen = 0; // 0 - main 
/**
 * Puts cursors in a given position. For example, position = 20 would place it in
 * the first line 20th column, position = 80 will place in the first column of the second line.
 */
void put_cursor(unsigned short pos) {
    out(0x3D4, 14);
    out(0x3D5, ((pos >> 8) & 0x00FF));
    out(0x3D4, 15);
    out(0x3D5, pos & 0x00FF);
}

/**
 * In order to avoid execution of arbitrary instructions by CPU we halt it.
 * Halt "pauses" CPU and puts it in low power mode until next interrupt occurs.
 */
_Noreturn void halt_loop() {
    while (1) { halt(); }
}
void comand_manager(char* comand, char* command_argument) {
    needToScrollCheck();
    if (my_strcmp(comand, "clear") == 0) {
        clear_shell();
    }
    else if (my_strcmp(comand, "edit") == 0) {
        saveScreen();
        edit_file(command_argument);
    }
    else if (my_strcmp(comand, "read") == 0) {
        read_file(command_argument);
    }
    else if (my_strcmp(comand, "load") == 0) {
        loadScreen();
    }
    else if (my_strcmp(comand, "create") == 0) {
        create_file(command_argument);
    }
    else if (my_strcmp(comand, "list") == 0){
        list_files();
    }
    else if (my_strcmp(comand, "delete") == 0) {
        delete_file(command_argument);
    }
    else if (my_strcmp(comand, "sleep") == 0) {
        screen = 1;
    }
    else {
        write_message("No such command", 0x4);
    }
}


int sec = 0;
void timer_tick_handler() {
    sec++;
 if (sec % 3 == 0){
     if (screen == 1) {
         sleep();
     }
}

}

/**
 * This is where the bootloader transfers control to.
 */
void kernel_entry() {
    init_kernel();
    keyboard_set_handler(key_handler);
    timer_set_handler(timer_tick_handler);

    clear_shell();
    halt_loop();
}
