/**********************************************************************
 * IC74HC595.cpp - ADT for accessing a 74HC595 SIPO buffer.
 * 2022 (c) Paul Reeve <preeve@pdjr.eu>
 */

#include <cstddef>
#include <Arduino.h>
#include "IC74HC595.h"

IC74HC595::IC74HC595(unsigned char gpioClock, unsigned char gpioData, unsigned char gpioLatch) {
  this->gpioClock = gpioClock;
  this->gpioData = gpioData;
  this->gpioLatch = gpioLatch;
  this->state = 0;
  this->updateInterval = 0UL;
  this->callback = 0;
}

void IC74HC595::begin() {
  pinMode(this->gpioClock, OUTPUT);
  pinMode(this->gpioData, OUTPUT);
  pinMode(this->gpioLatch, OUTPUT);
  this->writeByte(0);
}

void IC74HC595::write(unsigned int status, unsigned int count) {
  digitalWrite(this->gpioLatch, 0);
  while (count--) {
    shiftOut(this->gpioData, this->gpioClock, MSBFIRST, (status >> (8 * count)));
  }
  digitalWrite(this->gpioLatch, 1);
  this->state = state;
}

void IC74HC595::writeByte(unsigned char status) {
  this->write(status);
}

void IC74HC595::writeBit(int bit, int state) {
  if (state) {
    this->state |= (1UL << bit);
  } else {
    this->state &= ~(1UL << bit);
  }
  this->writeByte(this->state);
}

void IC74HC595::configureUpdate(unsigned long updateInterval, unsigned char (*callback)()) {
  this->updateInterval = updateInterval;
  this->callback = callback;
}

void IC74HC595::updateMaybe(bool force) {
  static unsigned long deadline = 0UL;
  unsigned long now = millis();

  if ((now > deadline) || force) {
    this->writeByte(this->callback());
    deadline = (now + this->updateInterval);
  }

}