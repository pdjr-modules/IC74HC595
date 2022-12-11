/**********************************************************************
 * IC74HC595.h - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 * 
 * * 
 * The 74HC595 is an 8-bit serialto-parallel I/O buffer. This library
 * allows the host application to write the buffer.
 * 
 * Example:
 * 
 * #define PisoDataGpio 2
 * #define PisoLatchGpio 3
 * #define PisoClockGpio 4
 * #define MyInterestingBit 6
 * 
 * IC74HC165 piso = IC74HC165(PisoDataGpio, PisoLatchGpio, PisoClockGpio);
 * 
 * void setup() {
 *   piso.begin();
 * }
 * 
 * void loop() {
 *   uint8_t byte;
 *   int bit;
 *
 *   byte = piso.readByte();
 *   bit = piso.readBit(MyInterestingBit); 
 * }
 * 
 */

#ifndef IC74HC595_H
#define IC74HC595_H

class IC74HC165 {
  public:
    IC74HC595(uint8_t gpioData, uint8_t gpioLatch, uint8_t gpioClock);
    void begin();
    void writeByte(uint8_t state);
    void writeBit(int bit, int state);
  private:
    uint8_t gpioData;
    uint8_t gpioLatch;
    uint8_t gpioClock;
    uint8_t state;
};

#endif