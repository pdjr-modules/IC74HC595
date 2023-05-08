/**
 * @file IC74HC595.h
 * @author Paul Reeve (preeve@pdjr.eu)
 * @brief Interface for the 74HC595 SIPO buffer. 
 * @version 0.1
 * @date 2023-02-08
 * @copyright Copyright (c) 2023
 */

#ifndef IC74HC595_H
#define IC74HC595_H

/**
 * @brief Interface to the IC74HC595 SIPO buffer IC.
 *
 * The IC74HC595 is an 8-bit serial-in parallel-out (SIPO) buffer IC
 * that is commonly used to expand microcontroller output capacity.  
 */
class IC74HC595 {

  public:

    /**
     * @brief Construct a new IC74HC595 object.
     *
     * \a gpioClock, \a gpioData and \a gpioLatch identify the host
     * microcontroller GPIO pins used for the SIPO interface connections.
     *
     * \a bufferCount specifies the number of ICs making up the
     * daisy-chained buffer.
     * Buffer updates are passed as an integer value so the max number
     * of buffers supported by the library depends upon the host
     * system's integer implementation: on a system with 32-bit
     * integers this abstraction can support up to 4 SIPO buffers.
     *
     * @param gpioClock - GPIO pin connected to IC pin (clock).
     * @param gpioData - GPIO pin connected to IC pin (data).
     * @param gpioLatch - GPIO pin connected to IC pin (latch).
     * @param bufferCount - optional number of ICs in the buffer daisy-chain (defaults to one).
     */
    IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch, unsigned int bufferCount = 1);

    /**
     * @brief Set the I/O mode of the configured GPIO pins.
     * 
     * Initialises the GPIO pins for buffer control.
     * This method must be called from setup() before any attempt is
     * made to send data to the buffer.
     */
    void begin();
    
    /**
     * @brief Set the outputs of one or more buffer ICs to a specified state.
     *
     * Each bit in \a status defines the output state of a single
     * parallel output channel: bits  through 7 define the status of
     * the first buffer IC in any daisy chain; bits 8 through 15 the
     * status of any second IC and so on.
     *
     * The number of low order bits to be written can be specified
     * in buffer sized chunks by \a buffers: if this argument is omitted
     * or set to zero then the \a bufferCount value supplied at
     * instantiation (or its default) will be used in its stead.
     *
     * @param status - the value to be written to the buffer.
     * @param buffers - the number of buffer ICs to be updated.
     */
    void write(unsigned int status, unsigned int buffers = 0);

    /**
     * @brief Set the state of a single parallel output.
     * 
     * When it is not appropriate to set all buffer outputs in a single
     * operation, this method can be used to set a single parallel
     * output channel by specifying the channel and the value to which
     * it should be set.
     *
     * @param bit - index of the output channel to be set (0..31).
     * @param state - the value to be assigned (0 or 1).
     */
    void writeBit(unsigned int bit, unsigned int state);
    
    /**
     * @brief 
     * 
     * @param updateInterval 
     * @param callback 
     */
    void configureCallback(unsigned int (*callback)(unsigned int buffer), unsigned long callbackInterval = 1000UL);
    
    /**
     * @brief 
     * 
     * @param force 
     */
    void callbackMaybe(bool force = false);
    
  private:
    unsigned char gpioClock;
    unsigned char gpioData;
    unsigned char gpioLatch;
    unsigned int buffer;
    unsigned int bufferCount;

    unsigned int (*callback)(unsigned int buffer);
    unsigned long callbackInterval;

};

#endif