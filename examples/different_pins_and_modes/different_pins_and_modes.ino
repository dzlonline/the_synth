// Arduino synth library Output mode example.

// The synth can output audio in three modes on two different pins:

// OUTA = Arduino PIN 11
// OUTB = Arduino PIN 3

// or

// Differntial on PINA,PINB

//Hardware connection(s):

//                           +10µF 
//PIN 11 (OUTA)---[ 1k ]--+---||--->> Audio out
//                        |
//                       === 10nF
//                        |
//                       GND

//                           +10µF 
//PIN 3 (OUTB) ---[ 1k ]--+---||--->> Audio out
//                        |
//                       === 10nF
//                        |
//                       GND

// Differential mode gives twice the voltage swing and may be better for driving piezos or speakers directly.
// Here are some examples:

// PIN 11 (OUTA) ------- Speaker/Piezo +

// PIN 3 (OUTB)  ------- Speaker/Piezo -

// Or better with a low pass filter

// PIN 11 (OUTA) ----+
//                   |
//                    )
//                    ) 10mH inductor
//                    )
//                   |
//                   +---- Speaker/Piezo +
//                   |
//                  === 1µF
//                   |
//PIN 3 (OUTB)  -----+---- Speaker/Piezo -






#include "synth.h"
synth edgar;

void setup() {

  //You select the output mode when starting the synth. You may re-start any time in any mode by calling apropriate begin()
  //Uncomment desired:
  
  edgar.begin();        //Default OUTA
  //edgar.begin(CHA);     //CHA (same as default)
  //edgar.begin(CHB);     //CHB
  //edgar.begin(DIFF);    //Differential
  
  //  Set up the voices
  edgar.setupVoice(0,SINE,60,ENVELOPE0,90,64);
  edgar.setupVoice(1,SINE,62,ENVELOPE1,90,64);
  edgar.setupVoice(2,SINE,64,ENVELOPE2,90,64);
  edgar.setupVoice(3,SINE,67,ENVELOPE0,90,64);


  edgar.begin();    //-Default OUTA
  //-Play a little gong
  edgar.trigger(0);
  delay(1000);
  edgar.trigger(1);
  delay(1000);
  edgar.trigger(2);
  delay(1000);
  edgar.trigger(3);
  delay(1000);


}
void loop() 
{
}






