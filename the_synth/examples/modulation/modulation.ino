// Arduino synth library modulation example

//Hardware connections:

//                    +10µF 
//PIN 11 ---[ 1k ]--+---||--->> Audio out
//                  |
//                 === 10nF
//                  |
//                 GND

// DZL 2014
// HTTP://dzlsevilgeniuslair.blogspot.dk
// HTTP://illutron.dk

#include <synth.h>

synth edgar;    //-Make a synth

void setup()
{

  edgar.begin();  //-Start it up

  //Set up a voice:
  //setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], length[0-127], mod[0-127, 64=no mod])

  edgar.setupVoice(0,SINE,65,ENVELOPE1,70,64);
}

void loop()
{
  for(int i=30;i<104;i+=10)
  {
      edgar.setMod(0,i);
      edgar.trigger(0);
     delay(1000);
  }
}
