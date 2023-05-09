/**
 * @file IC74HC595.h
 * @author Paul Reeve (preeve@pdjr.eu)
 * @brief Interface to the 74HC595 SIPO buffer. 
 * @version 0.1
 * @date 2023-02-08
 * @copyright Copyright (c) 2023
 */

#ifndef IC74HC595_H
#define IC74HC595_H

/**
 * @brief Interface to the IC74HC595 SIPO buffer IC.
 *
 * The IC74HC595 is an 8-channel serial-in-parallel-out (SIPO) buffer
 * IC that is commonly used to expand microcontroller output capacity.
 *
 * Multiple buffer ICs can be daisy-chained to increase the size of
 * the available buffer.
 * In this abstraction the state of all buffer output channels is
 * represented by an integer 'status' value which on architectures
 * with 32-bit integers limits the maximum number of operable buffer
 * ICs is four.
 */
class IC74HC595 {

  public:

    /**
     * @brief Construct a new IC74HC595 object.
     *
     * @param gpioClock - GPIO pin connected to the buffer clock input.
     * @param gpioData - GPIO pin connected to the buffer data pin.
     * @param gpioLatch - GPIO pin connected to the buffer data pin.
     */
    IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch);

    /**
     * @brief Set the IO mode of the configured GPIO pins to OUT.
     *
     * This method must be called from setup() before any attempt is
     * made to write data to the buffer.
     */
    void begin();
    
    /**
     * @brief Set the outputs of connected buffer ICs to a specified state.
     *
     * Each bit in \a status defines the output state of a single
     * parallel output channel: bits 0 through 7 define the states of
     * channels 0 through 7 on the first buffer IC in any daisy chain;
     * bits 8 through 15 the states of channels 0 throgh 7 on any
     * second buffer IC and so on.
     *
     * @param status - the value to be written to the buffer.
     * @param buffers - the number of buffer ICs to be updated (optional, defaults to 1).
     */
    void write(unsigned int status, unsigned int buffers = 1);

    /**
     * @brief Set the state of a single parallel output.
     * 
     * When it is not appropriate to set the state of all buffer
     * outputs in a single operation, this method can be used to set a
     * single parallel output channel by specifying the output channel
     * number (in the range 0 through 31) and the value to which it
     * should be set.
     *
     * @param state - the value to be assigned (0 or 1).
     * @param bit - index of the output channel to be set (defaults to 1).
     */
    void writeBit(unsigned int state, unsigned int bit = 0);
    
    /**
     * @brief Configure a callback function to provide regular status updates.
     *
     * The callback function will be invoked every \a interval
     * milliseconds and passed the current buffer status as its only
     * argument.
     * The callback must return a new status value which will be
     * promptly written to the buffer.
     *
     * @param callback - a callback function.
     * @param updateInterval - interval between invocations of \a callback in milliseconds (optional: defaulst to 1s).
     * @param buffers - the number of buffer ICs to be updated (optional: defaults to one).
     */
    void configureCallback(unsigned int (*callback)(unsigned int buffer), unsigned long updateInterval = 1000UL, unsigned int buffers = 1);
    
    /**
     * @brief Call any configured callback function at the configured interval.
     * 
     * This method should be called from loop() and will trigger an
     * invocation of any configured callback function at its specified
     * update interval or, optionally, immediately.
     *
     * @param force - if true, forces an immediate invocation of any configured callback (optional: default to false).
     */
    void callbackMaybe(bool force = false);
    
  private:
    unsigned char gpioClock;
    unsigned char gpioData;
    unsigned char gpioLatch;
    unsigned int status;

    unsigned int (*callback)(unsigned int buffer);
    unsigned long callbackInterval;
    unsigned int callbackBuffers;

};

#endif