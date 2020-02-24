/*
  toshiba_ic.h - Library for controlling the Toshiba ICs TC9162, TC9163, TC9164, and TC9459.
  Created by Frank von Zeppelin, February 23rd, 2020.
  Released into the public domain.
*/

// freie Verwendung für private Zwecke
// für kommerzielle Zwecke nur nach Genehmigung durch den Autor.

// protected under the friendly Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License
// http://creativecommons.org/licenses/by-nc-sa/3.0/

#pragma once
#include <stdint.h>

enum channel_t{LEFT, RIGHT, BOTH};

class Toshiba_IC
{
  public:
    Toshiba_IC(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin);
    void sendCommand(const uint8_t switchConfig, channel_t channel);
    uint8_t dataPin, clockPin, strobePin;
    uint8_t address = 0;
    void sendByte(const uint8_t data);
    void sendBit(const uint8_t data);
  
  private:
    void initializePins();
};

class TC9162 : public Toshiba_IC
{
  public:
    TC9162(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin) : Toshiba_IC(dataPin, clockPin, strobePin){}
    uint8_t address = 0;
};

class TC9163 : public Toshiba_IC
{
  public:
    TC9163(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin) : Toshiba_IC(dataPin, clockPin, strobePin){}
    uint8_t address = 1;
};

class TC9164 : public Toshiba_IC
{
  public:
    TC9164(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin) : Toshiba_IC(dataPin, clockPin, strobePin){}
    uint8_t address = 2;
};

class TC9459 : public Toshiba_IC
{
  public:
    TC9459(const uint8_t  dataPin, const uint8_t clockPin, const uint8_t strobePin, const uint8_t address);
    void sendCommand(const uint8_t leftVolume, const uint8_t rightVolume, const bool loudness);
};
