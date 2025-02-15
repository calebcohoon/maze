/*
 * keyboard.c
 *
 * Implementation of keyboard interrupt handler
 */

#include "keyboard.h"

#include <conio.h>
#include <dos.h>

/* Internal variables */
static void(__interrupt __far *orig_keyboard_handler)(void);
static unsigned char key_states[MAX_SCANCODES];

/*
 * keyboard_handle: Custom interrupt handler for keyboard input
 *
 * Reads scan code and updates key states
 * Chains to original handler
 */
static void _interrupt __far keyboard_handler(void) {
    unsigned char scancode;

    /* Read scan code from keyboard */
    scancode = inp(KEYBOARD_PORT);

    /* Update key state - bit 7 indicates key release */
    if (scancode < MAX_SCANCODES) {
        if (scancode & 0x80) {
            /* Key release - clear bit */
            key_states[scancode & 0x7F] = 0;
        } else {
            /* Key press - set bit */
            key_states[scancode] = 1;
        }
    }

    /* Chain to original handler */
    _chain_intr(orig_keyboard_handler);
}

/*
 * keyboard_init: Initialize keyboard handler
 *
 * Saves original handler and installs our custom handler
 */
void keyboard_init(void) {
    int i;

    /* Save original handler and install ours */
    orig_keyboard_handler = _dos_getvect(KEYBOARD_INT);

    /* Clear key states */
    for (i = 0; i < MAX_SCANCODES; i++) {
        key_states[i] = 0;
    }

    /* Install our handler */
    _dos_setvect(KEYBOARD_INT, keyboard_handler);

    /* Enable interrupts */
    _enable();
}

/*
 * keyboard_shutdown: Restore original keyboard handler
 */
void keyboard_shutdown(void) {
    _dos_setvect(KEYBOARD_INT, orig_keyboard_handler);
}

/*
 * is_key_pressed: Check if a specific key is currently pressed
 *
 * Parameters:
 *   scancode - Scan code of the key to check
 *
 * Returns:
 *   1 if key is pressed, 0 if not
 */
int is_key_pressed(unsigned char scancode) {
    if (scancode < MAX_SCANCODES) {
        return key_states[scancode];
    }

    return 0;
}

/*
 * update_key_state: Update keyboard state
 *
 * Should be called each frame to process any queued keyboard input
 */
void update_key_state(void) {
    /* Process any pending keyboard input */
    while (inp(KEYBOARD_STATUS) & 0x01) {
        inp(KEYBOARD_PORT);
    }
}
