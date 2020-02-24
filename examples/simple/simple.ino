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
