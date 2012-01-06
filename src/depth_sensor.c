/** 
@mainpage
    Simple depth sensor

    @author  Andy Goldstein\n
             Company : VideoRay LLC
*/

#include <device.h>
#include <uart.h>
#include <led.h>
#include <servo.h>
#include <sysclk.h>
#include <depth.h>
#include <spi.h>

#include <util/delay.h>

#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/eeprom.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


char VERSION[3] = {1,0,0};

void device_reset(void) {
    asm("jmp 0xFC00");  //jump to bootloader 
}


void system_init(void) {
    device_init();
	
    led_init();
    
	spi_init();

    uart_init();
    
	sysclk_init();

	depth_init();

    interrupt_enable();
	
}

//Sets the output rate
const int OUTPUT_DELAY_mS = 500;
char output[128];

int main(void) {
	unsigned long last_second = 0;

	//Setup everything
    system_init();

 	uart_set_baudrate(COMM_PORT_TETHER,115200);

    wdt_enable(WDTO_500MS);

	led(1);
	_delay_ms(250);
	led(0);

    for(;;) {  //spin forever, service the wdt, read the sensor, and output at some fixed rate

	   wdt_reset();

	   depth_acq();
	   
	   /***
  	    * Output the data sentence
	    * Here we use an nmea like sentence
	    * VRDT (videoray depth temp)
	    * The format is: "$PVRDT, DD, TT\r\n"
		* Where DD is the pressure in mBar and TT is the temp in Deg C/100
        **/
  	    if (get_time()-last_second>SYS_CLK_MS_2_TICKS(OUTPUT_DELAY_mS)) {
		   last_second = get_time();
		   sprintf(output,"$PVRDT,%d, %d\r\n",depth_mBar(), water_temp_cC()); 
		   uart_write(COMM_PORT_TETHER,output,strlen(output));
		}
	}
}

