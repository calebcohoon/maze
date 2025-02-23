/*
 * keyboard.h
 *
 * Keyboard interrupt handler and key state tracking
 * Uses INT 9h for direct keyboard access
 */

#ifndef KEYBOARD_H
#define KEYBOARD_H

/* Keyboard constants */
#define KEYBOARD_INT    0x09 /* IRQ1 keyboard interrupt */
#define KEYBOARD_PORT   0x60 /* Keyboard data port */
#define KEYBOARD_STATUS 0x64 /* Keyboard status port */
#define MAX_SCANCODES   123  /* Number of scan code to track */

/* Common scan codes */
#define SC_ESC   0x01
#define SC_LEFT  0x4B
#define SC_RIGHT 0x4D
#define SC_UP    0x48
#define SC_DOWN  0x50

/* Function prototypes */
void keyboard_init(void);
void keyboard_shutdown(void);
int is_key_pressed(unsigned char scancode);
void update_key_state(void);

#endif /* KEYBOARD_H */
