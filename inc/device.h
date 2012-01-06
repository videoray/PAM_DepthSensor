#ifndef __DEVICE_H__
#define __DEVICE_H__

#include <avr/io.h>   
#include <avr/interrupt.h> 
/** @file   device.h
 *  @brief  Functions and structures related to the basic interaction 
 *          of the low level hardware.
 *
 *          Used to set initial values processor registers, i/o lines, etc.
 *          Also acts as an abstraction layer for portability.  
 */


 #ifdef __PLATFORM_PRO4__
 #include <pro4.h>
 #else
 #error "A Platform must be defined in the Makefile!"
 #endif
 
/** Gloablly enable interrupts */
#define interrupt_enable()       sei()
/** Gloablly disable interrupts */
#define interrupt_disable()      cli() 

//@{
/** @name Interrupt_Helpers Some helper defines for checking/storing the GEI
*/

#define interrupt_check()        (SREG & 0x80)
#define interrupt_reg()          (SREG)
#define interrupt_save(x)        (x=SREG;)
#define interrupt_restore(x)     (SREG=x;)

/** Start a critical function
 *
 * CRITICAL_region_begin() can be used at the top of a scope block to make data 
 * access interrupt safe.  There must be a matching call to 
 * CRITICAL_region_end().  
 *
 * The macro expands to instantiate a local variable, so placement of the
 * macro may be restricted if the compiler is non-C99 conforming.
 *
 * The function should not return between the CRITICAL_region_begin() and 
 * CRITICAL_region_end() calls.
 *
 * @code Example:
         void test() {
            CRITICAL_region_begin();
                some_global_var=100;
                do_something_safe();
                do_something_else_safe();
            CRITICAL_region_end();
                not_safe_anymore();
         }
    @endcode
 */
#define CRITICAL_region_begin()         volatile unsigned char __intreg = SREG; cli()

/** End a critical function
 *
 * CRITICAL_region_end() is used in conjunction with CRITICAL_region_begin() to make data 
 * access interrupt safe.  
 */
#define CRITICAL_region_end()          SREG = __intreg
//@}


/** Top level api for all basic device initialization
 */
void device_init(void);

/** Reset the device
 *  Should be implemented in a device specific file, but is defined here 
 *  to insure that implementation is consistant.
 */
void device_reset(void);

#endif
