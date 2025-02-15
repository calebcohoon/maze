/*
 * timer.h
 *
 * Game timing and main loop functionality
 * Uses PC's 8254 Programmable Interval Timer for accurate timing
 */

#ifndef TIMER_H
#define TIMER_H

/* Timer Constants */
#define TIMER_INT     0x08 /* IRQ0 - System timer interrupt */
#define TIMER_PORT    0x40 /* 8254 PIT port address */
#define TIMER_CONTROL 0x43 /* PIT control register port */
#define TIMER_VALUE   1193 /* Value for ~1000Hz (1.193182MHz / 1000Hz) */
#define TIMER_PER_SEC 1000 /* Desired timer frequency in Hz */

/* Game state structure */
typedef struct {
    unsigned long ticks;       /* Total timer ticks since start */
    unsigned long last_time;   /* Last frame's tick count */
    unsigned long delta_time;  /* Time elapsed since last frame */
    unsigned long frame_count; /* Total frames rendered */
    int is_running;            /* Main loop control flag */
} game_state_t;

/* Function Prototypes */
void timer_init(void);
void timer_shutdown(void);
void update_timing(game_state_t *state);
unsigned long get_ticks(void);

#endif /* TIMER_H */
