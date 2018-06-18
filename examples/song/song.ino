//Example based on this demo:
//https://github.com/electricmango/Arduino-Music-Project.git
//

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
#include "notes.h"
#include "song.h"

synth edgar;

void setup() 
{
  Serial.begin(19200);
  edgar.begin(DIFF);

  edgar.setupVoice(0,SINE,60,ENVELOPE0,80,64);
  edgar.setupVoice(1,SINE,62,ENVELOPE0,100,64);
  edgar.setupVoice(2,SINE,64,ENVELOPE2,110,64);
  edgar.setupVoice(3,SINE,67,ENVELOPE0,110,64);


  for (int thisNote = 0; thisNote < 1000; thisNote++) {

    /*
    to calculate the note duration, take one second divided by the note type.
     e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
     */
    int noteDuration = 800/noteDurations[thisNote];
    //    tone(8, melody[thisNote],noteDuration);

    if(melody[thisNote]<=NOTE_E4)
      edgar.mTrigger(1,melody[thisNote]+32);
    else
      edgar.mTrigger(0,melody[thisNote]+32);
    delay(noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }

}

void loop() 
{

}


