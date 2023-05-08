# class `IC74HC595` 

Interface to the [IC74HC595](#classIC74HC595) SIPO buffer IC.

The [IC74HC595](#classIC74HC595) is an 8-bit serial-in parallel-out (SIPO) buffer IC that is commonly used to expand microcontroller output capacity.

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`IC74HC595`](#classIC74HC595_1ad6a63f4598d3b419bb3a98010f00ab75)`(unsigned char gpioClock,unsigned char gpioData,unsigned char gpioLatch,unsigned int bufferCount)` | Construct a new [IC74HC595](#classIC74HC595) object.
`public void `[`begin`](#classIC74HC595_1a66416a0c85080cd00c3ebede9fca3f7b)`()` | Set the I/O mode of the configured GPIO pins.
`public void `[`write`](#classIC74HC595_1a7d87b0e7410edd336dd72ee9ab8499c4)`(unsigned int status,unsigned int buffers)` | Set the outputs of one or more buffer ICs to a specified state.
`public void `[`writeBit`](#classIC74HC595_1adaf39e8c1f9dae013304ba8725bf29ff)`(unsigned int bit,unsigned int state)` | Set the state of a single parallel output.
`public void `[`configureCallback`](#classIC74HC595_1aedb307231bf7d0f42d9eaf0abb0e3c45)`(unsigned int(*)(unsigned int buffer) callback,unsigned long callbackInterval)` | Configure a callback function to provide regular status updates.
`public void `[`callbackMaybe`](#classIC74HC595_1a9b94635c84aedde3e0df7452a0139763)`(bool force)` | Call any configured callback function at the configured interval.

## Members

#### `public  `[`IC74HC595`](#classIC74HC595_1ad6a63f4598d3b419bb3a98010f00ab75)`(unsigned char gpioClock,unsigned char gpioData,unsigned char gpioLatch,unsigned int bufferCount)` 

Construct a new [IC74HC595](#classIC74HC595) object.

*gpioClock*, *gpioData* and *gpioLatch* identify the host microcontroller GPIO pins used for the SIPO interface connections.

*bufferCount* specifies the number of ICs making up the daisy-chained buffer. Buffer updates are passed as an integer value so the max number of buffers supported by the library depends upon the host system's integer implementation: on a system with 32-bit integers this abstraction can support up to 4 SIPO buffers.

#### Parameters
* `gpioClock` - GPIO pin connected to IC pin (clock). 

* `gpioData` - GPIO pin connected to IC pin (data). 

* `gpioLatch` - GPIO pin connected to IC pin (latch). 

* `bufferCount` - optional number of ICs in the buffer daisy-chain (defaults to one).

#### `public void `[`begin`](#classIC74HC595_1a66416a0c85080cd00c3ebede9fca3f7b)`()` 

Set the I/O mode of the configured GPIO pins.

Initialises the GPIO pins for buffer control. This method must be called from setup() before any attempt is made to send data to the buffer.

#### `public void `[`write`](#classIC74HC595_1a7d87b0e7410edd336dd72ee9ab8499c4)`(unsigned int status,unsigned int buffers)` 

Set the outputs of one or more buffer ICs to a specified state.

Each bit in *status* defines the output state of a single parallel output channel: bits through 7 define the status of the first buffer IC in any daisy chain; bits 8 through 15 the status of any second IC and so on.

The number of low order bits to be written can be specified in buffer sized chunks by *buffers:* if this argument is omitted or set to zero then the *bufferCount* value supplied at instantiation (or its default) will be used in its stead.

#### Parameters
* `status` - the value to be written to the buffer. 

* `buffers` - the number of buffer ICs to be updated.

#### `public void `[`writeBit`](#classIC74HC595_1adaf39e8c1f9dae013304ba8725bf29ff)`(unsigned int bit,unsigned int state)` 

Set the state of a single parallel output.

When it is not appropriate to set all buffer outputs in a single operation, this method can be used to set a single parallel output channel by specifying the channel and the value to which it should be set.

#### Parameters
* `bit` - index of the output channel to be set (0..31). 

* `state` - the value to be assigned (0 or 1).

#### `public void `[`configureCallback`](#classIC74HC595_1aedb307231bf7d0f42d9eaf0abb0e3c45)`(unsigned int(*)(unsigned int buffer) callback,unsigned long callbackInterval)` 

Configure a callback function to provide regular status updates.

The callback function will be passed the current buffer status as its only argument and it should return a possibly updated status which will be promptly written to the buffer.

#### Parameters
* `updateInterval` - interval between invocations of *callback* in milliseconds. 

* `callback` - a callback function.

#### `public void `[`callbackMaybe`](#classIC74HC595_1a9b94635c84aedde3e0df7452a0139763)`(bool force)` 

Call any configured callback function at the configured interval.

This method should be called from loop() and will make sure that the configured calling frequency is honoured unless *force* is supplied and true in which case the callback function will be invoked immediately.

#### Parameters
* `force`

Generated by [Moxygen](https://sourcey.com/moxygen)