#ifndef __SPI_H__
#define __SPI_H__

/** @file   spi.h
 *  @brief  Low level driver for SPI interface
 *
 *          Handles control of SPI port 
 *
 *          Currently SPI is always used in polled mode and does not
 *          make use of interupts for data transmission or reception.
 */
 
 /** Maximum number of supported SPI Ports */
#define MAX_SPI 1

#define SPI_CLK_RISING  0
#define SPI_CLK_FALLING 1

#define SPI_CLK_PHASE_SAMPLE_LEADING  0
#define SPI_CLK_PHASE_SAMPLE_TRAILING 1

//@{
/** @name IO line defines */
#define SPI_PORT     PORTB
#define SPI_PORT_DIR DDRB


#define SPI_SS 	 (1<<0)
#define SPI_SCLK (1<<1)
#define SPI_MOSI (1<<2)
#define SPI_MISO (1<<3)
//@}

/** Initialize the serial peripheral interface subsystem 
 */ 
void spi_init(void);

/** Send a byte out the SPI, waits for transmission to be complete 
 *
 *  @param port SPI port
 *  @param outbyte data to be written
 */ 
void spi_write(int port, char outbyte);

/** Send a byte out the SPI, does NOT wait for transmission to be complete or 
 *  return data word to be available.  
 *
 *  @param port SPI port
 *  @param outbyte data to be written
 */ 
void spi_write_noblock(int port, char outbyte);

/** Waits for transmission to be complete and return data to be available */
void spi_wait(int port);

/** Sends a null byte (0x0) out the SPI, and waits for the return value
 *
 *  @param port SPI port
 *  @return data byte recieved
 */ 
char spi_read(int port);

/** Send a byte out the SPI, wait for transmission to be complete and 
 *  return data word to be available. 
 *
 *  @param port SPI port
 *  @param outbyte data to be written
 *  @return data byte recieved
 */ 
char spi_rw(int port, char outbyte);

/** Switch the polarity for the clock line
 *
 *  @param port SPI port
 *  @param falling_edge set to 1 to have the clock leading edge be a high to low
 *          transition.  If falling_edge == 1 then the clk line is high on idle.
 */
void spi_set_clock_polarity(int port, char falling_edge);

/** Switch the phase of data sampling vs the clock line
 *
 *  @param port SPI port
 *  @param sample_on_trailing_edge set to 1 to data sampled on the trailing edge
 *         of the clock pulse.  If sample_on_trailing_edge == 1 then data is 
 *         setup on the leading edge of the clock pulse.  Whether this falling 
 *         or rising edge depends upon the polatity of the clock signal.
 */
void spi_set_clock_phase(int port, char sample_on_trailing_edge);
#endif
