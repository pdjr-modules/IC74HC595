# IC74HC595

ADT for operating a 74HC595 serial-in-parallel-out (SIPO) buffer.

## Constructors

### IC74HC595 *mySipo*(*gpioClock*, *gpioData*, *gpioLatch*);
```
IC74HC595 mySipo(10, 11, 12);
```

## Methods

### begin()
```
mySipo.begin(;
```

### writeByte(*byte*)
```
mySipo.writeByte(0x05);
```
Set the parallel outputs on IC channels A through H to values
of *byte* bits 0 through 7 respectively.

### writeBit(*bit*, *state*)
```
mySipo.writeBit(0, 1);
```


 
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
