/**********************************************************************
 * IC74HC595.cpp - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include <Arduino.h>
#include <IC74HC595.h>

IC74HC595::IC74HC595(uint8_t gpioClock, uint8_t gpioData, uint8_t gpioLatch) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
}

void IC74HC595::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, OUTPUT);
  pinMode(this->gpioLatch, OUTPUT);
  this->writeByte(0);
}

void IC74HC595::writeByte(uint8_t state) {
  digitalWrite(this->gpioLatch, 0);
  shiftOut(this->gpioData, this->gpioClock, MSBFIRST, state);
  digitalWrite(this->gpioLatch, 1);
  this->state = state;
}

void IC74HC595::writeBit(int bit, int state) {
  if (state) {
    this->state |= (1UL << bit);
  } else {
    this->state &= ~(1UL << bit);
  }
  this->writeByte(this->state);
}

void IC74HC595::configureUpdate(unsigned long updateInterval, uint8_t (*dataFunction)()) {
  this->updateInterval = updateInterval;
  this->dataFunction = dataFunction;
}

void IC74HC595::updateMaybe(bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || force) {
    this->writeByte(this->dataFunction());
    deadline = (now + this->updateInterval);
  }

}