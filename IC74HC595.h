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

class IC74HC595 {

  public:

    /**
     * @brief Construct a new IC74HC595 object
     * 
     * @param gpioClock - GPIO pin connected to IC pin (clock).
     * @param gpioData - GPIO pin connected to IC pin (data).
     * @param gpioLatch - GPIO pin connected to IC pin (latch).
     * @param bufferCount - the number of ICs in the buffer dais-chain
     * (defaults to one).
     */
    IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch, unsigned int bufferCount = 1);

    /**
     * @brief Set the I/O mode of the configured GPIO pins.
     * 
     * Best called from setup().
     */
    void begin();
    
    /**
     * @brief Set the status of the buffer to a specified value.
     * 
     * If bufferLength (specified when the instance was created) is 1
     * then status is a byte value to be assigned to the buffer and
     * must be passed by reference. For example:
     * ```
     * uint8_t v = 0xff;
     * myBuffer.write(&x);
     * ```
     * Otherwise status is taken to be an array of byte values which
     * will be written to successive ICs in the buffer daisy-chain. 
     */
    void write(unsigned int status);

    /**
     * @brief 
     * 
     * @param bit 
     * @param state 
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