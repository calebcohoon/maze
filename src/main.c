#include <conio.h> /* For kbhit() */
#include <dos.h>   /* For int386() and union REGS */
#include <string.h>/* For memset() */

/* VGA/Video Constants */
#define VIDEO_INT 0x10    /* BIOS video interrupt number */
#define SET_MODE  0x00    /* AH value for set video mode */
#define MODE_13H  0x13    /* AL value for Mode 13h */
#define MODE_TEXT 0x03    /* AL value for 80x25 text mode */
#define VGA_BASE  0xA0000 /* Video memory base address */

/* Screen dimensions */
#define SCREEN_WIDTH  320                            /* Mode 13h width in pixels */
#define SCREEN_HEIGHT 200                            /* Mode 13h height in pixels */
#define SCREEN_SIZE   (SCREEN_WIDTH * SCREEN_HEIGHT) /* Total pixels/bytes */

/* Our internal, private back buffer for drawing */
static unsigned char back_buffer[SCREEN_SIZE];

/*
 * set_mode: Changes the video mode using BIOS interrupt 0x10
 *
 * Parameters:
 *   mode - The desired video mode:
 *          0x13 for 320x200 256-color mode
 *          0x03 for 80x25 text mode
 *
 * Notes:
 * - Uses int386() for 32-bit protected mode interrupt call
 * - Sets AX register directly (AH=0 for set mode, AL=mode)
 */
void set_mode(unsigned char mode) {
    union REGS regs;

    regs.w.ax = mode; /* Set both AH (function) and AL (mode) at once */

    int386(VIDEO_INT, &regs, &regs);
}

/*
 * flip_buffer: Copies the back buffer to video memory
 *
 * Notes:
 * - Copies entire screen buffer in one operation
 * - Should be called after all drawing is complete
 */
void flip_buffer(void) {
    memcpy((void *) VGA_BASE, back_buffer, SCREEN_SIZE);
}

int main() {
    int x = 0;

    /* Enter mode 13h (320x200 256-color) */
    set_mode(MODE_13H);

    while (!kbhit()) {
        memset(back_buffer, 0, SCREEN_SIZE);

        /* Draw a moving pixel */
        back_buffer[x + (SCREEN_HEIGHT / 2) * SCREEN_WIDTH] = 1;
        x = (x + 1) % SCREEN_WIDTH;

        /* Present the buffer to the screen */
        flip_buffer();
    }

    /* Return to text mode */
    set_mode(MODE_TEXT);

    return 0;
}
