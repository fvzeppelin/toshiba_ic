/* 
 * This file is part of the toshiba_ic library for Arduino (https://github.com/fvzeppelin/toshiba_ic).
 * Copyright (c) 2020 Frank von Zeppelin.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
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
  this->sendByte(switchConfig);

  if ((channel == RIGHT) || (channel == BOTH))
    this->sendBit(1);
  else
    this->sendBit(0);

  if ((channel == LEFT) || (channel == BOTH))
    this->sendBit(1);
  else
    this->sendBit(0);
  
  this->sendAddress();
  this->sendEnd();
}

void Toshiba_IC::sendByte(const uint8_t data)
{
  shiftOut(this->dataPin, this->clockPin, LSBFIRST, data);
}

void Toshiba_IC::sendBit(const uint8_t data)
{
  digitalWrite(this->dataPin, !(data==0));
  digitalWrite(this->clockPin, HIGH);
  digitalWrite(this->clockPin, LOW);  
}

void Toshiba_IC::sendAddress()
{
  for (int i=0; i<4; i++)
    this->sendBit(!!((this->address()) & (1 << i)));
}

void Toshiba_IC::sendEnd()
{
  digitalWrite(this->strobePin, HIGH);
  digitalWrite(this->strobePin, LOW);
  // delay needed at the end as consecutive calls of sendCommand() wouldn't work
  delay(1);
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
  this->m_address = address;
}

void TC9459::sendCommand(uint8_t leftAttenuation, uint8_t rightAttenuation, const bool loudness)
{
  // maximum value of attenuation is -90db
  if (leftAttenuation > 90)
    leftAttenuation = 90;
  if (rightAttenuation > 90)
    rightAttenuation = 90;
  
  this->sendByte(leftAttenuation);
  this->sendByte(rightAttenuation);

  this->sendBit(loudness);

  for (int i=0; i<3; i++)
    this->sendBit(0);

  this->sendAddress();
  this->sendEnd();
}
