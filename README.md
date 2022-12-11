# IC74HC595

ADT for accessing a 74HC595 SIPO buffer.

The 74HC595 is an 8-bit serialto-parallel I/O buffer. This library
allows the host application to write the buffer.
 
Example:
``` 
#define SopiDataGpio 2
#define SopiLatchGpio 3
#define SopiClockGpio 4

#define MyInterestingBit 6
 
IC74HC595 sopi = IC74HC595(SopiDataGpio, SopiLatchGpio, SopiClockGpio);

void setup() {
  sopi.begin();
}
 
void loop() {
  sopi.writeByte(0xff);
  sopi.writeBit(MyInterestingBit, 0); 
}
```
