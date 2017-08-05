// Arduino synth library MIDI example
//
// The arduino receives MIDI over Serial at 31250 BAUD
//
// Each of the four voices are assigned to MIDI channel 1,2,3 and 4
// For each channel:
// NOTE_ON with velocity over zero triggers voice. 
// Controller 13 controls waveform: SINE[0-21] TRIANGLE[22-42] SQUARE[43-63] SAW[64-84] RAMP[85-105] NOISE[106-127]
// Controller 12 controls envelope: ENVELOPE0[0-32] ENVELOPE1[33-64] ENVELOPE2[65-96] ENVELOPE3[97-127]
// Controller 10 controls length: [0-127]
// Controller 7  controls modulation: negative[0-63] neutral[64] positive[65-127]
// You can change Controller numbers and the Baudrate in settings.h
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
#include "MIDI_parser.h"
#include "settings.h"

synth edgar;        //-Make a synth
midiParser parser;  //-Make a MIDI parser

void setup() 
{
  Serial.begin(MIDI_BAUDRATE);    //MIDI BAUD rate
  edgar.begin();                    //Init synth
}

void loop()
{
  unsigned char voice;
  while(Serial.available())
  {
    if(parser.update(Serial.read()))  //-Feed MIDI stream to parser and execute commands
    {
      switch(parser.midi_cmd)
      {
        //*********************************************
        // Handle MIDI notes
        //*********************************************
      case 0x90: //-Channel 1 (voice 0)
      case 0x91: //-Channel 2 (voice 1)
      case 0x92: //-Channel 3 (voice 2)
      case 0x93: //-Channel 4 (voice 3)

        voice = parser.midi_cmd-0x90;
        if(parser.midi_2nd)  //-Velocity not zero (could implement NOTE_OFF here)
          edgar.mTrigger(voice,parser.midi_1st);
        break;

        //*********************************************
        // Handle MIDI controllers
        //*********************************************
      case 0xb0:  //-Channel 1 (voice 0)
      case 0xb1:  //-Channel 2 (voice 1)
      case 0xb2:  //-Channel 3 (voice 2)
      case 0xb3:  //-Channel 4 (voice 3)
        voice=parser.midi_cmd-0xb0;
        switch(parser.midi_1st)  //-Controller number
        {
        case WAVEFORM_CNTRL:  //-Controller 13 
          edgar.setWave(voice,parser.midi_2nd/21);
          break;
        case ENVELOPE_CNTRL:  //-Controller 12
          edgar.setEnvelope(voice,parser.midi_2nd/32);
          break;   
        case LENGTH_CNTRL:  //-Controller 10
          edgar.setLength(voice,parser.midi_2nd);
          break;  
        case MODULATION_CNTRL:   //-Controller 7
          edgar.setMod(voice,parser.midi_2nd);
          break;
        }
        break;
      }
    }
  }
}



