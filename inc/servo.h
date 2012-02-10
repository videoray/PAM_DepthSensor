#ifndef __SERVO_H__
#define __SERVO_H__

/** @file   servo.h
 *  @brief  Controls servos and devices which accept servo like control signals
 *
 *          Provides a basic servo API and handles interrupt driven servo 
 *          cycling.  Currently the servos are controlled by multiplexing a 
 *          timer output to generate teh servo pulses.  This is handled 
 *          automatically by the api.
 *
 *          Timer 1 output compare A is used for driving the servos.
 */
 
/** Maximum number of servo devices supported. */
#define MAX_SERVO_COUNT (9)


 
/** Servo mux clock rate */ 
#define SERVO_CLK (F_CPU/8)
/** Helper define for setting servo pulse width values */
#define SERVO_SET_mS(X) (X * SERVO_CLK/1000)

/** Initialize the entire serve sub-system 
 *  
 *  servo_init() will intiallize all servo outputs 
 *  The servo control hardware will start sending output signals immediatly. 
 */
void servo_init(void);


/** Sets index which causes the servo mux to reset and start over      
 *  @param index highest indexed servo 
 */
void servo_set_active_servos(int index );

/** Sets the servo output signal based upon a real value from -1 to 1       
 *  @param servo_id 
 *  @param val output signal value
 */
void servo_set(int servo_id, float val);

/** Sets the servo output signal to a specific mS pulse       
 *  @param servo_id 
 *  @param pulse_mS width of servo pulse in mS
 */
void servo_set_mS(int servo_id, float pulse_mS);

/** Sets the servo output signal based upon an input of servo clk ticks       
 *  @param servo_id 
 *  @param clks number of servo clks to use for output signal
 */
void servo_set_clks(int servo_id, unsigned int clks);

/** Gets the current clock setting for servo channel       
 *  @param servo_id 
 *  @return servo clks value 
 */
 unsigned int servo_get_clks(int servo_id);


/** Sets the servo output signal by adding a delta amount to the current servo value     
 *  @param servo_id 
 *  @param delta number of servo clks to add to current value can be + or -
 */
void servo_adj_clks(int servo_id, int delta);

/** Sets limits on the servo output signal based on mS pulse widths       
 *
 *  The servo output drive will never be set beyond the set limits regardless
 *  of values the user passes into the set functions.
 *
 *  @param servo_id 
 *  @param min_mS mS equavalent minimum number of servo clks to use
 *  @param max_mS mS equavalent maximum number of servo clks to use
 */
void servo_set_range(int servo_id, 
                     float min_mS, 
                     float max_mS); 
 
/** Sets limits on the servo output signal based upon servo clk ticks       
 *
 *  The servo output drive will never be set beyond the set limits regardless
 *  of values the user passes into the set functions.
 *
 *  @param servo_id 
 *  @param min_clks minimum number of servo clks to use for output signal
 *  @param max_clks maximum number of servo clks to use for output signal
 */
void servo_set_range_clks(int servo_id, 
                          unsigned int min_clks, 
                          unsigned int max_clks); 
  
/** Sets limits on the servo output signal based upon mS      
 *
 *  The servo output drive will never be set beyond the set limits regardless
 *  of values the user passes into the set functions.
 *
 *  The servo limits will be set to:
        zero point-limit to zero point+limit
 *
 *  @param servo_id 
 *  @param zero_mS servo zero point
 *  @param limit_mS servo limit
 */
void servo_set_zero_and_limit(int servo_id, 
                          float zero_mS, 
                          float limit_mS); 
  
/** Sets limits on the servo output signal based upon servo clk ticks       
 *
 *  The servo output drive will never be set beyond the set limits regardless
 *  of values the user passes into the set functions.
 *
 *  The servo limits will be set to:
        zero point-limit to zero point+limit
 *
 *  @param servo_id 
 *  @param zero_clks clks to use as servo zero point
 *  @param limit_clks number of servo clks use for servo range
 */
void servo_set_zero_and_limit_clks(int servo_id, 
                          unsigned int zero_clks, 
                          unsigned int limit_clks); 
                         
/** Sets servo slew       
 *
 *  The servo output approach the target by adding this amount on each update
 *
 *  @param servo_id 
 *  @param min_clks number of servo clks to inc/dec on each update
 */
void servo_set_slew_clks(int servo_id,
                         int delta);
                         
/** Sets servo slew       
 *
 *  The servo output approach the target by adding this amount on each update
 *
 *  @param servo_id 
 *  @param min_clks number of servo clks to inc/dec on each update
 */
void servo_set_slew(int servo_id,
                    float delta_mS);
                         
                         
/** Sets servo deadband       
 *
 *  Set the deadband for the servo in mS
 *
 *  @param servo_id 
 *  @param deadband_mS mS to use as deadband on either side 
 *                        of center point
 */
void servo_set_deadband(int servo_id,
                        float deadband_mS);

                        
/** Sets servo deadband       
 *
 *  Set the deadband for the servo in clks
 *
 *  @param servo_id 
 *  @param deadband_clks number of servo clks to use as deadband on either side 
 *                        of center point
 */
void servo_set_deadband_clks(int servo_id,
                        int deadband_clks);


/** Sets the actual timer registers for the servo control 
 *
 *  Currently only implemented when using timer direct driving of servos
 */
void servo_set_actual_direct(void);
#endif

