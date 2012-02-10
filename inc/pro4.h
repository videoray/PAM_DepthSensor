#ifndef __PRO4__
#define __PRO4__

#include <types.h>

/** @file   pro4.h
 *  @brief  HW abstraction layer for the pro4 platform
 *
 *          Provides defines sets to abstract specific hardware Ports, adc 
 *          channels, etc. from the actual devices.  The defines in this file
 *          are used by the lower level drivers.  If a specific driver requires a
 *          define and it is not present, the compiler will throw an error.
 *
 *          This file or other platform specific abstractions are automatically
 *          included by device.h based upon the platform define which should be
 *          present in the MakeFile.
 *
 */

 
/* For reference:
 *  Timer 0 is used for PWM control of lights.
 *  Timer 1 is used to drive the servos via a decade counter
 *  Timer 2 & 3 are currently not used 
 */
 
/* Various IO Port defines used by the lower level drivers */
 
#define UART_RS485_TXE_PORT PORTA
#define UART_RS485_TXE_PORT_DIR DDRA
#define UART_0_RS485_TXE_MASK (1<<1)
#define UART_1_RS485_TXE_MASK (1<<0)

#define LIGHTS_PORT     PORTB
#define LIGHTS_PORT_DIR DDRB
#define LIGHTS_IO      (1<<4)
 
#define SERVO_MUX_PORT     PORTA
#define SERVO_MUX_PORT_DIR DDRA
#define SERVO_MUX_CLK     (1<<2)
#define SERVO_MUX_RST     (1<<3)

#define LED_PORT        PORTA
#define LED_PORT_DIR    DDRA
#define LED             (1<<4)
#define LED2			(1<<7)
 
#define CAMERA_CONTROL_PORT      PORTC
#define CAMERA_CONTROL_PORT_DIR  DDRC   
#define CAMERA_CONTROL_PORT_MASK 0xFF 

#define CAMERA_SWITCH_PORT     PORTG
#define CAMERA_SWITCH_PORT_DIR DDRG
#define CAMERA_SWITCH          (1<<2)

#define POWER_CONTROL_PORT     PORTG
#define POWER_CONTROL_PORT_DIR DDRG

/*Power bus on PRO 4 is active LOW so init state should be 1 */
#define POWER_BUS_TETHER       (0)
#define POWER_BUS_12V          (1<<0)
#define POWER_BUS_INIT_STATE   (POWER_BUS_12V)

/* SPI Port Defines (there is only one) */
#define DEPTH_PORT 0
#define DEPTH_ENABLE_PORT     PORTE
#define DEPTH_ENABLE_PORT_DIR DDRE
#define DEPTH_ENABLE          (1<<2)

/* Predefined SERVO Channels */
#define SERVO_THRUSTER_PORT      0
#define SERVO_THRUSTER_STARBOARD 1
#define SERVO_THRUSTER_VERT      2
#define SERVO_TILT               4
#define SERVO_FOCUS              5 

/* TOTAL number of adc channels available in the system, this includes all ADC devices */
#define ADC_MAX_CHANNELS 8

/* Predefined MCU ADC Channels */
#define ADC_TETHERVOLT     0
#define ADC_12VOLT         1
#define ADC_12VOLT_CURRENT 2
#define ADC_MOISTURE       3
#define ADC_TEMP_CPU       4
#define ADC_TEMP_POWER     5  
#define ADC_PRESSURE       6



#define COMM_PORT_TETHER     0
#define COMM_PORT_ACCESSORY  1

/** Predefined Version specific features */
#define VERSION_SUPPORTS_TIMER_DIRECT_SERVO	1


#define HARDWARE_CONFIG_ADDR		((char*) 0x20)

/** get the device hardware configuration data
 *  @param buf buffer for data
 *  @field data field to read
 *  @param len max size of buffer, in general should be equal to size-of the hardware config structure 
 */
void get_hwconfig(char* buf, int field, int len);

/** Size of individual data fields in standard generic hardware config struct
 */
#define PRO4_HW_CONFIG_FIELD_LEN 32

/** Hardware config structure for the PRO4 
 */
typedef struct HARDWARE_CONFIG_PRO4_tag {
	uint32_t DataStructVersionNumber;
	char BOARD_REV_CPU[PRO4_HW_CONFIG_FIELD_LEN];
	char BOARD_REV_POWER[PRO4_HW_CONFIG_FIELD_LEN];
	char BOARD_REV_DEPTH[PRO4_HW_CONFIG_FIELD_LEN];
	char BOARD_REV_CAMERA_IO[PRO4_HW_CONFIG_FIELD_LEN];
	char DEVICE_REV_CAMERA[PRO4_HW_CONFIG_FIELD_LEN];
	char DEVICE_REV_LIGHTS[PRO4_HW_CONFIG_FIELD_LEN];
	char DEVICE_REV_THRUSTER_HORIZ[PRO4_HW_CONFIG_FIELD_LEN];
	char DEVICE_REV_THRUSTER_VERT[PRO4_HW_CONFIG_FIELD_LEN];
} HARDWARE_CONFIG_PRO4;	


/** Predefined Version specific features */
#define VERSION_SUPPORTS_TIMER_DIRECT_SERVO	1
#define VERSION_SUPPORTS_FAST_LED_FET 		2
#define VERSION_SUPPORTS_EMI_FILTER_MOD		3

/** defined available temp sensors */
#define TEMP_SENSOR_CPU 	ADC_TEMP_CPU
#define TEMP_SENSOR_POWER 	ADC_TEMP_POWER

#endif
