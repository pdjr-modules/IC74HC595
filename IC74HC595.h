/**********************************************************************
 * IC74HC595.h - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#ifndef IC74HC595_H
#define IC74HC595_H

class IC74HC595 {
  public:
    IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch);
    void begin();
    void writeByte(unsigned char state);
    void writeBit(int bit, int state);
    void configureUpdate(unsigned long updateInterval, unsigned char(*callback)());
    void updateMaybe(bool force = false);
  private:
    unsigned char gpioClock;
    unsigned char gpioData;
    unsigned char gpioLatch;
    unsigned char state;
    unsigned long updateInterval;
    unsigned char (*callback)();
};

#endif