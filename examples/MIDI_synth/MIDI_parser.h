// Simple MIDI parser
// Call update with MIDI stream
// Returns 1 when a command is redy for execution
// Command is available in midi_cmd
// Oprand(s) available in midi_1st and midi_2nd;
// Dzl 2014

class midiParser
{
public:
  unsigned char midi_state;
  unsigned char midi_cmd;
  unsigned char midi_1st;
  unsigned char midi_2nd;

  midiParser()
  {
    midi_state=0;
    midi_cmd=0;
    midi_1st=0;
    midi_2nd=0;
  }

  unsigned char update(unsigned char c)
  {
    switch(midi_state)
    {
    case 0:
      switch(c&0xF0)
      {
      case 0x80:
      case 0x90:
      case 0xB0:
        {
          midi_state=1;
          midi_cmd=c;
        };
        break;
      }
      break;

    case 1:		//-Get 1
      if(c&0x80)
      {
        midi_state=0;
        break;
      }
      midi_1st=c;
      midi_state=2;
      break;

    case 2:		//-Get 2
      if(c&0x80)
      {
        midi_state=0;
        break;
      }
      midi_2nd=c;
      midi_state=0;

      return 1;        //-Command ready
      break;
    }
    return 0;          //-Nothing to do
  }
};




