/**********************************************************************
 * IC74HC595.cpp - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include <Arduino.h>
#include "IC74HC595.h"

IC74HC595::IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch, unsigned int bufferCount) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
  this->bufferCount = bufferCount;
  this->buffer = 0;
}

void IC74HC595::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, OUTPUT);
  pinMode(this->gpioLatch, OUTPUT);
  this->write(this->buffer);
}

void IC74HC595::write(unsigned int status) {
  this->buffer = status;
  digitalWrite(this->gpioLatch, 0);
  for (unsigned int i = 0; i < this->bufferCount; i++) {
    shiftOut(this->gpioData, this->gpioClock, MSBFIRST, (this->buffer >> ((this->bufferCount - 1) * 8)) & 0xff);
  }
  digitalWrite(this->gpioLatch, 1);
}

void IC74HC595::writeBit(unsigned int bit, unsigned int state) {
  if (state) {
    this->buffer |= (1UL << bit);
  } else {
    this->buffer &= ~(1UL << bit);
  }
  this->write(this->buffer);
}

void IC74HC595::configureCallback(unsigned int (*callback)(unsigned int buffer), unsigned long callbackInterval) {
  this->callback = callback;
  this->callbackInterval = callbackInterval;
}

void IC74HC595::callbackMaybe(bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || force) {
    this->write(this->callback(this->buffer));
    deadline = (now + this->callbackInterval);
  }

}
