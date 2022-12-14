/**********************************************************************
 * IC74HC595.h - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#ifndef IC74HC595_H
#define IC74HC595_H

class IC74HC595 {
  public:
    IC74HC595(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch);
    void begin();
    void writeByte(uint8_t state);
    void writeBit(int bit, int state);
    void configureUpdate(unsigned long updateInterval, uint8_t(*callback)());
    void updateMaybe(bool force = false);
  private:
    uint8_t gpioClock;
    uint8_t gpioData;
    uint8_t gpioLatch;
    uint8_t state;
    unsigned long updateInterval;
    uint8_t (*callback)();
};

#endif