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

// simple example for the configuration used in my HK3490 input board

#include <toshiba_ic.h>

#define STROBE 2
#define DATA 3
#define CLOCK 4
#define VOLUMECONTROLADDRESS 8

TC9163 sourceSelect(DATA, CLOCK, STROBE);
TC9164 monitorSelect(DATA, CLOCK, STROBE);
TC9459 volumeControl(DATA, CLOCK, STROBE, VOLUMECONTROLADDRESS);

void setup() {
  // put your setup code here, to run once:
}

void loop() {
  // put your main code here, to run repeatedly:

  sourceSelect.sendCommand(2, BOTH);
  monitorSelect.sendCommand(17, BOTH);
  volumeControl.sendCommand(255,255, false);

  while (1);
}
