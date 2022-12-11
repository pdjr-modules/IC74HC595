/**********************************************************************
 * IC74HC595.cpp - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include <Arduino.h>
#include <IC74HC595.h>

IC74HC595::IC74HC595(uint8_t gpioData, uint8_t gpioLatch, uint8_t gpioClock) {
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
  this->gpioClock = gpioClock;
}

void IC74HC595::begin() {
  pinMode(this->gpioData, OUTPUT);
  pinMode(this->gpioLatch, OUTPUT);
  pinMode(this->gpioClock, OUTPUT);
  this->writeByte(0);
}

void IC74HC165::writeByte(int state) {
  digitalWrite(this->gpioLatch, LOW);
  retval = shiftOut(this->gpioData, this->gpioClock, MSBFIRST, state);
  digitalWrite(this->gpioLatch. HIGH);
  this->state = state;
}

void IC74HC165::writeBit(int bit, int state) {
  if (state) {
    this->state |= (1UL << bit);
  } else {
    this->state &= ~(1UL << bit);
  }
  digitalWrite(this->state);
}
