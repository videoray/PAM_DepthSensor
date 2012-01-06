#ifndef __LED_H__
#define __LED_H__

/** @file   led.h
 *  @brief  API for blinking the diagnostic LED
 */

 #define LED_ON  1
 #define LED_OFF 0
 
/** Initialize the LED driver
 */
void led_init(void);

/** Single API function for LED control
 *
 *  @param led ID of the LED (LED or LED2 on PRO4)
 *  @param on state of LED
 */
void led_control(int led, char on);

/** Turn ON/OFF the main diagnostic LED
 *
 *  @param on state of LED
 */
void led(char on);

/** Turn ON/OFF the second diagnostic LED
 *
 *  @param on state of LED
 */
void led2(char on);

/** Turn ON the main diagnostic LED
 */
void led_on(void);

/** Turn OFF the main diagnostic LED
 */
void led_off(void);

#endif
