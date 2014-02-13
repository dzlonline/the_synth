// Arduino synth library absolute frequency example

//Hardware connections:

//                    +10µF 
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND


#include <synth.h>

synth edgar;    //-Make a synth

void setup() {

  edgar.begin();                                   //-Start it up
  edgar.setupVoice(0,TRIANGLE,60,ENVELOPE1,127,64);  //-Set up voice 0
}

void loop()
{
  edgar.setFrequency(0,50.0);
  edgar.trigger(0);
  delay(1000);
  edgar.setFrequency(0,60.0);
  edgar.trigger(0);
  delay(1000);
  edgar.setFrequency(0,440.0);
  edgar.trigger(0);
  delay(1000);
  edgar.setFrequency(0,1000.0);
  edgar.trigger(0);
  delay(1000);
}
