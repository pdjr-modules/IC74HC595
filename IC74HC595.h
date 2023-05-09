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
 * @brief ADT representing an IC74H595-based parallel output buffer.
 *
 * The IC74HC595 IC is an 8-channel serial-in-parallel-out (SIPO)
 * buffer.
 * Multiple IC74H595's can be daisy-chained to increase the number
 * of available output channels in increments of eight. 
 *
 * In this abstraction the state of all buffer output channels is
 * represented by an integer 'status' value which on architectures
 * with 32-bit integers limits the maximum number of daisy-chained
 * buffers that can be operated to four.
 */
class IC74HC595 {

  public:

    /**
     * @brief Construct a new buffer.
     *
     * @param gpioClock - GPIO pin connected to the IC74H595 clock pin.
     * @param gpioData - GPIO pin connected to the IC74H595 data pin.
     * @param gpioLatch - GPIO pin connected to the IC74H595 data pin.
     * @param buffer - number of IC74HC595 ICs in the buffer daisy-chaine (optional: defaults to 1).
     */
    IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch, unsigned int buffer = 1);

    /**
     * @brief Initiliase the buffer.
     *
     * This method must be called from setup() before any attempt is
     * made to write data to the buffer.
     * It sets the GPIO pin modes and sets all buffer outputs OFF.
     */
    void begin();
    
    /**
     * @brief Set multiple buffer outputs to a specified state.
     *
     * Each bit in \a status defines the output state of a single
     * parallel output channel: bits 0 through 7 define the states of
     * channels 0 through 7 on the first buffer IC in any daisy chain;
     * bits 8 through 15 the states of channels 0 throgh 7 on any
     * second buffer IC and so on.
     *
     * The \a mask value can be used to restrict updates to just those
     * channels selected by an active bit in the \a mask value.
     *
     * @param status - the value to be written to the buffer.
     * @param mask - buffer channels to be updated (optional: default is 0xffffffff which says all channels).
     */
    void write(unsigned int status, unsigned int mask);
    
    /**
     * @brief Configure buffer updates by a scheduled callback.
     *
     * The callback function will be invoked every \a updateInterval
     * milliseconds and passed the current buffer status as its only
     * argument.
     * The callback must return a new status value which will be
     * promptly written to the buffer.
     *
     * @param callback - a callback function.
     * @param updateInterval - interval between invocations of \a callback in milliseconds (optional: defaults to 1s).
     */
    void configureCallback(unsigned int (*callback)(unsigned int buffer), unsigned long updateInterval = 1000UL);
    
    /**
     * @brief Invoke any configured callback.
     * 
     * This method should typically be called from loop() with no
     * \a force to trigger an invocation of any configured callback
     * function at the configured update interval.
     * The method can be call with \a force set to true to invoke an
     * immediate callback.
     *
     * @param force - if true, forces an immediate invocation of any configured callback (optional: default to false).
     */
    void callbackMaybe(bool force = false);
    
  private:
    unsigned char gpioClock;
    unsigned char gpioData;
    unsigned char gpioLatch;
    unsigned int buffers;
    unsigned int status;

    unsigned int (*callback)(unsigned int buffer);
    unsigned long callbackInterval;

};

#endif