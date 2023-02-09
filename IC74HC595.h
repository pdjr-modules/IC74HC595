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
     */
    IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch);

    /**
     * @brief Set the I/O mode of the configured GPIO pins.
     * 
     * In Arduino world this method should be called from setup().
     */
    void begin();
    
    /**
     * @brief Set the status of one or more connected buffers from a
     * specified value.
     * 
     * @param status - the bit values to be assigned to the buffers.
     * Bits 0-7 for buffer 0, 8-15 for buffer 1 and so on. Defaults
     * to 0.
     * @param count - the number of buffer ICs to be updated (defaults
     * to 1). 
     */
    void write(unsigned int status = 0U, unsigned int count = 1U);

    /**
     * @brief Set the status of the first connected buffer.
     * 
     * @param status - the bit values to be assigned to the buffer.
     * Defaults to 0.
     */
    void writeByte(unsigned char status = 0);

    void writeBit(int bit, int state);
    void configureUpdate(unsigned long updateInterval, unsigned char(*callback)());
    void updateMaybe(bool force = false);
  private:
    unsigned char gpioClock;
    unsigned char gpioData;
    unsigned char gpioLatch;
    unsigned int state;
    unsigned long updateInterval;
    unsigned char (*callback)();
};

#endif