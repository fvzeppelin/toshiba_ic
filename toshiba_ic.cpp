/*
  toshiba_ic.cpp - Library for controlling the Toshiba ICs TC9162, TC9163, TC9164, and TC9459.
  Created by Frank von Zeppelin, February 23rd, 2020.
  Released into the public domain.
*/

#include "toshiba_ic.h"
#include <Arduino.h> 

Toshiba_IC::Toshiba_IC(const uint8_t dataPin, const uint8_t clockPin, const uint8_t strobePin)
{
  this->dataPin = dataPin;
  this->clockPin = clockPin;
  this->strobePin = clockPin;
  this->initializePins();
}

void Toshiba_IC::sendCommand(const uint8_t switchConfig, const channel_t channel)
{
  digitalWrite(this->strobePin, LOW);
  digitalWrite(this->clockPin, LOW);
  
  this->sendByte(switchConfig);

  if ((channel == RIGHT) || (channel == BOTH))
    this->sendBit(1);
  else
    this->sendBit(0);

  if ((channel == LEFT) || (channel == BOTH))
    this->sendBit(1);
  else
    this->sendBit(0);
  
  for (int i=0; i<4; i++)
    this->sendBit(((this->address)>>i)&1);

  digitalWrite(this->strobePin, HIGH);
  digitalWrite(this->strobePin, LOW);

  delay(1);
}

void Toshiba_IC::sendByte(const uint8_t data)
{
  shiftOut(this->dataPin, this->clockPin, LSBFIRST, data);
}

void Toshiba_IC::sendBit(const uint8_t data)
{
  if (data==0)
    digitalWrite(this->dataPin, LOW);
  else
    digitalWrite(this->dataPin, HIGH);
  digitalWrite(this->clockPin, HIGH);
  digitalWrite(this->clockPin, LOW);  
}

void Toshiba_IC::initializePins()
{
  pinMode(this->dataPin, OUTPUT);
  pinMode(this->clockPin, OUTPUT);
  pinMode(this->strobePin, OUTPUT);

  digitalWrite(this->dataPin, LOW);
  digitalWrite(this->clockPin, LOW);
  digitalWrite(this->strobePin, LOW);
}

TC9459::TC9459(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin, const uint8_t address) : Toshiba_IC(dataPin, clockPin, strobePin)
{
  this->address = address;
}

void TC9459::sendCommand(const uint8_t leftVolume, const uint8_t rightVolume, const bool loudness)
{
  uint8_t leftVol = leftVolume;
  uint8_t rightVol = rightVolume;
  
  digitalWrite(this->strobePin, LOW);
  digitalWrite(this->clockPin, LOW);
  
  if (leftVol > 64)
    leftVol = 64;
  if (rightVol > 64)
    rightVol = 64;
  
  this->sendByte(leftVol);
  this->sendByte(rightVol);

  if (loudness)
    this->sendBit(1);
  else
    this->sendBit(0);
  for (int i=0; i<3; i++)
    this->sendBit(0);

  for (int i=0; i<4; i++)
    this->sendBit(((this->address)>>i)&1);

  digitalWrite(this->strobePin, HIGH);
  digitalWrite(this->strobePin, LOW);

  delay(1);
}
