#ifndef __SYSCLK_H__
#define __SYSCLK_H__

/** @file   sysclk.h
 *  @brief  Implements a 1mS system clock using 8-bit counter Timer2
 *
 *          Provides a symple system clock.  An interrupt driven timer is used
 *          to implement a 1 mS system clock.  The system time is a 32 bit number,
 *          where the 24 MSB are approx mS (as close as possible) and the LSB 8-bits
 *          are the timer counts.  The timer counts do not use the full 8 bits due
 *          to the source clock frequency available. 
 *
 *          Timer 2 output compare A is used.
 */
 
/** System clock source */
#define SYS_CLK_SRC (F_CPU/64)
/** System clk timer counts per uS */
#define SYS_CLK_PER_uS (1000000/SYS_CLK_SRC)
/** Helper macro to increment the mS portion of a long system time */
#define SYS_CLK_INC_TICKS(x) (x += (1<<8))
#define SYS_CLK_MS_2_TICKS(x) (((unsigned long)x)<<8)
 

/** Initialize the system clock sub-system */
void sysclk_init(void);  

/** Get the system time
 *
 *  @return 32-bit system time (24 MSb are approx mS, 8 LSb are timer cnts)
 */
unsigned long get_time(void);

/** Spin waiting for a number of mS to elapse */
void sysclk_wait_mS(unsigned int mS);

/** Get the system tick value
 * 
 *  The system tick value is the 24 MSb of the system time
 *  which are as close to 1mS increments as possible
 *
 *  @return system tick value 8 lsb will be 0
 */
unsigned long get_sysclk_ticks(void);

#endif
