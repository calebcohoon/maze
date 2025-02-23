/*
 * timer.c
 *
 * Implementation of game timing system
 */

#include "timer.h"

#include <conio.h>
#include <dos.h>

#include "keyboard.h"

static void(__interrupt __far *orig_timer_handler)(void);
static volatile unsigned long timer_ticks = 0;

/*
 * timer_handler: Custom interrupt handler for system timer
 *
 * Increments our tick counter and chains to the original handler
 */
static void __interrupt __far timer_handler(void) {
    timer_ticks++;

    _chain_intr(orig_timer_handler);
}

/*
 * timer_init: Initialize the timing system
 *
 * Sets up the PIT for 1000Hz interrupts and installs our handler
 */
void timer_init(void) {
    /* Save original interrupt handler */
    orig_timer_handler = _dos_getvect(TIMER_INT);

    /* Set timer frequency */
    outp(TIMER_CONTROL, 0x36);             /* Control byte: counter 0, mode 3*/
    outp(TIMER_PORT, TIMER_VALUE & 0xFF);  /* Low byte of count */
    outp(TIMER_CONTROL, TIMER_VALUE >> 8); /* High byte of count */

    /* Install our handler */
    _dos_setvect(TIMER_INT, timer_handler);

    /* Enable interrupts */
    _enable();
}

/*
 * timer_shutdown: Restore original timer state
 *
 * Restores original interrupt handler and timer frequency
 */
void timer_shutdown(void) {
    /* Restore original timer frequency */
    outp(TIMER_CONTROL, 0x36);
    outp(TIMER_PORT, 0);
    outp(TIMER_PORT, 0);

    /* Restore original handler */
    _dos_setvect(TIMER_INT, orig_timer_handler);
}

/*
 * get_ticks: Return current tick count
 *
 * Returns:
 *   Current number of timer ticks since initialization
 */
unsigned long get_ticks(void) {
    return timer_ticks;
}

/*
 * update_timing: Update timing information in game state
 *
 * Parameters:
 *   state - Pointer to game state structure to update
 */
void update_timing(game_state_t *state) {
    state->ticks = get_ticks();
    state->delta_time = state->ticks - state->last_time;
    state->last_time = state->ticks;
    state->frame_count++;
}

/*
 * game_init: Initialize game state
 *
 * Parameters:
 *   state - Pointer to game state structure to initialize
 */
void game_init(game_state_t *state) {
    state->ticks = 0;
    state->delta_time = 0;
    state->last_time = 0;
    state->frame_count = 0;
    state->is_running = 1;

    /* Initialize timer system */
    timer_init();
}

/*
 * game_shutdown: Clean up game systems
 *
 * Parameters:
 *   state - Pointer to game state structure
 */
void game_shutdown(game_state_t *state) {
    timer_shutdown();

    state->is_running = 0;
}

/*
 * game_update: Main game update function
 *
 * Parameters:
 *   state - Pointer to game state structure
 *
 * Returns:
 *   1 if game should continue, 0 if it should exit
 */
int game_update(game_state_t *state) {
    /* Update timing information */
    update_timing(state);

    /* Return 0 if ESC is pressed */
    if (is_key_pressed(SC_ESC)) {
        return 0;
    }

    return 1;
}
