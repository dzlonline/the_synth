#include "test_synth.h"
synth edgar;

/*************************************************
 * Public Constants
 *************************************************/

#define NOTE_B0  0
#define NOTE_C1  1
#define NOTE_CS1 2
#define NOTE_D1  3
#define NOTE_DS1 4
#define NOTE_E1  5
#define NOTE_F1  6
#define NOTE_FS1 7
#define NOTE_G1  8
#define NOTE_GS1 9
#define NOTE_A1  10
#define NOTE_AS1 11
#define NOTE_B1  12
#define NOTE_C2  13
#define NOTE_CS2 14
#define NOTE_D2  15
#define NOTE_DS2 16
#define NOTE_E2  17
#define NOTE_F2  18
#define NOTE_FS2 19
#define NOTE_G2  20
#define NOTE_GS2 21
#define NOTE_A2  22
#define NOTE_AS2 23
#define NOTE_B2  24
#define NOTE_C3  25
#define NOTE_CS3 26
#define NOTE_D3  27
#define NOTE_DS3 28
#define NOTE_E3  29
#define NOTE_F3  30
#define NOTE_FS3 31
#define NOTE_G3  32
#define NOTE_GS3 33
#define NOTE_A3  34
#define NOTE_AS3 35
#define NOTE_B3  36
#define NOTE_C4  37
#define NOTE_CS4 38
#define NOTE_D4  39
#define NOTE_DS4 40
#define NOTE_E4  41
#define NOTE_F4  42
#define NOTE_FS4 43
#define NOTE_G4  44
#define NOTE_GS4 45
#define NOTE_A4  46
#define NOTE_AS4 47
#define NOTE_B4  48
#define NOTE_C5  49
#define NOTE_CS5 50
#define NOTE_D5  51
#define NOTE_DS5 52
#define NOTE_E5  53
#define NOTE_F5  54
#define NOTE_FS5 55
#define NOTE_G5  56
#define NOTE_GS5 57
#define NOTE_A5  58
#define NOTE_AS5 59
#define NOTE_B5  60
#define NOTE_C6  61
#define NOTE_CS6 62
#define NOTE_D6  63
#define NOTE_DS6 64
#define NOTE_E6  65
#define NOTE_F6  66
#define NOTE_FS6 67
#define NOTE_G6  68
#define NOTE_GS6 69
#define NOTE_A6  70
#define NOTE_AS6 71
#define NOTE_B6  72
#define NOTE_C7  73 
#define NOTE_CS7 74
#define NOTE_D7  75
#define NOTE_DS7 76
#define NOTE_E7  77
#define NOTE_F7  78
#define NOTE_FS7 79
#define NOTE_G7  80
#define NOTE_GS7 81
#define NOTE_A7  82
#define NOTE_AS7 83
#define NOTE_B7  84
#define NOTE_C8  85
#define NOTE_CS8 86
#define NOTE_D8  87
#define NOTE_DS8 88



int melody[] = {
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3, 
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0, 
  NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_A3, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS3, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3, 
  NOTE_E4, NOTE_E3, NOTE_A2, NOTE_E3, NOTE_C4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_D4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_B3, NOTE_E3, NOTE_GS2, NOTE_E3,
  NOTE_C4, NOTE_E3, NOTE_E4, NOTE_E3, NOTE_A4, NOTE_E3, NOTE_A2, NOTE_E3, 
  NOTE_GS4, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3, NOTE_GS2, NOTE_E3,
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,

};


void setup() {
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
  //    edgar.setFrequency(0,440);
  edgar.trigger(0);
  delay(1000);
  edgar.trigger(1);
  delay(1000);
  edgar.trigger(2);
  delay(1000);
  edgar.trigger(3);
  delay(1000);
  /*  
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
   Serial.println(i);
   }
   */


}


