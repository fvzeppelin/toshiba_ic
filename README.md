# toshiba_ic
Simple library for controlling the Toshiba ICs TC9162, TC9163, TC9164, and TC9459 with an Arduino.  

It is tested with an Arduino Leonardo controlling one TC9163AF, one TC9164AF, and one TC9459F IC on the same DATA, CK, and ST lines.

## Usage
The library provides one class per IC type, which may be instantiated:  

    TC9162  
    TC9163  
    TC9164  
    TC9459  

`TC9162`, `TC9163`, and `TC9164` are instantiated in the same way:  

    TC9162 myIC(dataPin, clockPin, strobePin);  
where the parameters give the pin names of the three connected communication lines (s. extras/pinouts.txt):  

    dataPin = DATA  
    clockPin = CK  
    strobePin = ST  
After instantiation, the method  

    sendCommand(switchConfig, channel)  
may be used to request a switch configuration for one or two channels (`channel = {LEFT, RIGHT, BOTH}`). E.g. if you want to close only the switches S1 and S7 on both channels, use:  

    sendCommand(0b01000001, BOTH);  

The class `TC9459` must additionally be given the IC address (as wired by CS1 and CS2, s. datasheets) when instantiated:  

    TC9459 myTC9459(dataPin, clockPin, strobePin, address);  
For the `TC9459` class, the method  

    sendCommand(leftAttenuation, rightAttenuation, loudness)  
may be used to request the desired volume level and loudness. E.g. if you want to set the volume to -10dB attenuation and no loudness, use:  

    sendCommand(10, 10, false);  
