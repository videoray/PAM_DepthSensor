#ifndef __DEPTH_H__
#define __DEPTH_H__

/** @file   depth.h
 *  @brief  Support reading of depth sensor
 *
 *          API for depth sensor access.
 *
 *          Currently the Intersema MS5541 is the supported pressure sensor.
 *
 *          This depth sensor aquires temperature data as well.  This is the 
 *          temperature of the pressure sensing element, which we assume is at 
 *          the same temperature as the outside enviornment.
 *
 *          Due to the long conversion time of the sensor adc (35mS) per channel
 *          a timer based state machine is implemented.  It is assumed that the
 *          sysclk has been initialized and is running at a 1 mS tick rate.
 *
 *          The direct read functions can be used instead, but should not be used
 *          if the main api is used.  The direct read functions do require 
 *          depth_init to be called first. 
 */
 
/** @name Main API
 *  
 *  Standard API for accessing depth sensor data 
 */
//@{

/** Initialize the pressure sensor (depth) subsystem 
 *
 *  Requires that SPI has previously been initialized correctly to support 
 *  the device protocol.
 */ 
void depth_init(void);

/** Main driver function for the depth acquisition state machine 
 *
 *  This function must be called periodically.  A minimum of 4 invocations are
 *  required for depth data to be available.
 *
 *  Uses the sysclk module as a timebase.  Assumes sysclk ticks are 1 mS, but would
 *  work with ticks longer than 1mS.  
 *
 *  @return 1 new depth data available, otherwise 0
 */ 
char depth_acq(void);

float depth_psi(void);
float water_temp_C(void);
unsigned int depth_mpsi(void);
unsigned int depth_mBar(void);
unsigned int water_temp_cC(void);

//@}

/** @name Direct Read API
 *  
 *  API for more direct access to depth sensor data 
 */
//@{

/** Read directly and calculate the calibrated depth in psi along with temperature in degree C 
 *
 * This function will read both datum out of the sensor, it will take at least
 * 70 mS to return as the conversion time of the sensor is 35 mS for each datum.
 *
 * @return depth_psi depth in psi
 * @return temp_c temperature in degree C
 */
void depth_psi_and_temp(float *depth_psi, float *temp_c);


/** Read the depth sensor pressure datum 
 *
 * @return raw pressure value in device specific units
 */
unsigned int depth_raw(void);

/** Read and calculate the temperature compensated calibrated depth in mBar  
 *
 * @return pressure value in mbar
 */

unsigned int temp_raw(void);

//@}
#endif
