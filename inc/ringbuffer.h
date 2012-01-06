#ifndef __RINGBUFFER_H__
#define __RINGBUFFER_H__

/** @file   ringbuffer.h
 *  @brief  Support for arbitrary size ringbuffers
 */

/** Stucture supporting ring byte buffers 
*/
struct RingBuffer
{
    char *buf;          ///< pointer to data storage
    unsigned int size;  ///< size of data storage
    volatile unsigned int cnt;   ///< count of bytes in buffer
    volatile unsigned int rp;    ///< read pointer  (index)
    volatile unsigned int wp;    ///< write pointer (index) 
};
/** Initialize a ring buffer
 *  
 *  This function will initialize the various fields of the struct RingBuffer.
 *
 *  @param rb pointer to ringbuffer to initialize
 *  @param buf pointer to the storage buffer the ringbuffer should use
 *  @param size of the storage buffer (buf)  
 */
void ringbuf_init(struct RingBuffer *rb, char *buf, int size);
/** Flush a ring buffer */
void ringbuf_flush(struct RingBuffer *rb);

/** @return Number of bytes in buffer */
unsigned int ringbuf_cnt(struct RingBuffer *rb);

/** @return True if no space left in buffer */
int ringbuf_full(struct RingBuffer *rb);

/** @return True if buffer is empty */
int ringbuf_empty(struct RingBuffer *rb);

/** @return A byte out of the buffer */
unsigned char ringbuf_get(struct RingBuffer *rb);

/** Put a byte into the buffer
 *  @return False if buffer is full
 */
int ringbuf_put(struct RingBuffer *rb, unsigned char b);

/** Put bytes directly into the buffer, not checking for overruns or overwrites
 */
void ringbuf_put_direct(struct RingBuffer *rb, char *b, int cnt);

//@}

#endif