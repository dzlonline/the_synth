// Arduino synth library basic example

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

void setup() {

  edgar.begin();  //-Start it up

  //Set up the voices:
  //setupVoice( voice[0-3] , waveform[SINE,TRIANGLE,SQUARE,SAW,RAMP,NOISE] , pitch[0-127], envelope[ENVELOPE0-ENVELOPE3], length[0-127], mod[0-127, 64=no mod])

  edgar.setupVoice(0,SINE,60,ENVELOPE1,60,64);
  edgar.setupVoice(1,RAMP,0,ENVELOPE3,64,64);
  edgar.setupVoice(2,TRIANGLE,0,ENVELOPE2 ,70,64);
  edgar.setupVoice(3,NOISE,0,ENVELOPE3,20,64);
}

void loop()
{
  //-Plays some notes on the voices:
  
  for(int i=49;i<57;i++)
   {
     edgar.mTrigger(0,i);
     edgar.mTrigger(1,i);

     delay(300);

     edgar.setLength(3,30);
     edgar.mTrigger(3,i);

     delay(150);

     edgar.mTrigger(2,i);
     edgar.setLength(3,20);
     edgar.mTrigger(3,i);

     delay(150);
   }
}
