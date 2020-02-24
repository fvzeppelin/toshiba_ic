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

#pragma once
#include <stdint.h>

enum channel_t{LEFT, RIGHT, BOTH};

// base class which implements the basic communication features for all relevant ICs
// the base class is abstract, since the adress() method must be implemented for each specific IC
class Toshiba_IC
{
  public:
    Toshiba_IC(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin);
    void sendCommand(const uint8_t switchConfig, channel_t channel);
    uint8_t dataPin, clockPin, strobePin;
    virtual uint8_t address() = 0;
    void sendByte(const uint8_t data);
    void sendBit(const uint8_t data);
    void sendAddress();
    void sendEnd();
  
  private:
    void initializePins();
};

// derived class for TC9162 (address 0b0000)
class TC9162 : public Toshiba_IC
{
  public:
    TC9162(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin) : Toshiba_IC(dataPin, clockPin, strobePin){}
    uint8_t address() override {return 0;};
};

// derived class for TC9162 (address 0b0001)
class TC9163 : public Toshiba_IC
{
  public:
    TC9163(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin) : Toshiba_IC(dataPin, clockPin, strobePin){}
    uint8_t address() override {return 1;};
};

// derived class for TC9162 (address 0b0010)
class TC9164 : public Toshiba_IC
{
  public:
    TC9164(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin) : Toshiba_IC(dataPin, clockPin, strobePin){}
    uint8_t address() override {return 2;};
};

// derived class for TC9162 (address must be given at instantiation, allowed values are 0b10XX)
class TC9459 : public Toshiba_IC
{
  public:
    TC9459(const uint8_t dataPin, const uint8_t clockPin, const uint8_t strobePin, const uint8_t address);
    void sendCommand(uint8_t leftAttenuation, uint8_t rightAttenuation, const bool loudness);
    uint8_t address() override {return this->m_address;};
  private:
    uint8_t m_address;
};
