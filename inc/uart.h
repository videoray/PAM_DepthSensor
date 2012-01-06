#ifndef __UART_H__
#define __UART_H__

/** @file   uart.h
 *  @brief  Low level driver for async serial communications.
 *
 *          Handles interrupt drivin asynchronous serial communications 
 *          (RS-232/RS_485) for the MCU internal USART ports.
 */
 
 /** Maximum number of supported UART devices */
#define MAX_UARTS 2
 
 /** Predefined device_id for the internal mcu uarts. */
#define MCU_INTERNAL_UART_0 (0)
#define MCU_INTERNAL_UART_1 (1)

 
/** Initialize the entire uart sub-system 
 *  
 *  uart_init() will intiallize all uart devices, both chip internal and
 *              external.    
 *
 */
void uart_init(void);

/** Enable rs485 on a device that supports multiple serial physical layers*/
void uart_enable_rs485(int uart_device_id, int on_off);
 
/** Manually set the baudrate for a specific device 
 *  
 *  @param uart_device_id id of specific uart port
 *  @param baudrate baudrate to set
 *
 */
 void uart_set_baudrate(int uart_device_id, unsigned long baudrate);
 
//@{
/** @name Buffered UART functions.
 *
 *         Read/Write a number of bytes from/to the uart buffers.
 *         Since the actual communication in interrupt driven these functions
 *         only transfer data to/from buffers and possibly initiate interrupt 
 *         driven transmission.
 */
 
/** Get data from the uart buffer
 *
 *  @param uart_device_id id of specific uart port
 *  @param buf buffer for data to be received
 *  @param cnt count of bytes to transmit or receive, for read it's the max 
 *             count that can be read at once time (essentially size of buf)
 *  @return actual number of bytes read
 */
int uart_read(int uart_device_id, char *buf, int cnt);

/** Returns a single byte from the uart buffer 
 *
 *  This is a non-blocking read of the uart ringbuffer.  The end user should 
 *  insure that there is data available in the buffer prior to calling this 
 *  function (via uart_rx_cnt, for example).  An read on an empty buffer will
 *  return a 0.
 *
 *  @param uart_device_id id of specific uart port
 *  @return single byte from uart buffer, will return 0 if buffer is empty
 */
char uart_read_byte(int uart_device_id); 

/** Write data into the uart buffer and start transmission
 *
 *  @param uart_device_id id of specific uart port
 *  @param buf buffer for data to be sent
 *  @param cnt count of bytes to transmit
 *  @return actual number of bytes queued for transmission
 */
int uart_write(int uart_device_id, char *buf, int cnt);

/** Write a single byte into the uart buffer or out the port
 *
 *  Writes a single byte to the uart buffer or out the port if the
 *  buffer is empty.
 *
 *  @param uart_device_id id of specific uart port
 *  @param data byte to output
 *  @return 1 if data was written, 0 on failure (buffer full)
 */
int uart_write_byte(int uart_device_id, char data);

/** Wait for the uart ringbuffer and transmit register to be empty 
 *
 *  This functions insures that there are no further bytes to be transmitted 
  *  @param uart_device_id id of specific uart port
*/
void uart_wait_write(int uart_device_id);

/** Returns number of bytes int he receive buffer
 *  @param uart_device_id id of specific uart port
 */
int uart_rx_cnt(int uart_device_id);
//@}


 
 
//@{
/** @name Direct UART r/w functions
 *           
 *        Directly r/w data to the usart hardware.  These functions are blocking
 *        until hardware resources are available.
 */
 
 /** Read a byte from the uart 
 *
 *  @param uart_device_id id of specific uart port
 *  @return byte recieved
 */
char uart_getc(int uart_device_id);

 /** Write a byte to the uart 
 *
 *  @param uart_device_id id of specific uart port
 *  @param c byte to send
 */
void uart_putc(int uart_device_id, char c);
 
#endif