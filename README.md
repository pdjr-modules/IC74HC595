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
Set parallel output channel *bit* to *state* (0 or 1).

### configureUpdate(*interval*, *callback*)
```
uint8_t getData() {
  return(0x0f);
}

mySipo.configureUpdate(20, getData);
```
Configure automatic update parameters by setting the interval
between updates to *interval* milliseconds and specifying a
function *callback* which will be called by the update process
to recover a value for output each time *interval* expires.

### updateMaybe(*force*)
```
mySipo.updateMaybe();
```
Generally this method will be called from within the main program
loop() to update the IC output channels with a value returned from
the callback function each time the specified update interval expires.
```
mySipo.updateMaybe(true);
```
Can be called at any time to force an immediate update.

