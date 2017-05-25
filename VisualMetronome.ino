#include <MIDI.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

MIDI_CREATE_DEFAULT_INSTANCE();

// -----------------------------------------------------------------------------

// This function will be automatically called when a NoteOn is received.
// It must be a void-returning function with the correct parameters,
// see documentation here:
// http://arduinomidilib.fortyseveneffects.com/a00022.html

void handleNoteOn(byte channel, byte pitch, byte velocity)
{
  int r = 0;
  int g = 0;
  int b = 0;

  switch( pitch )
  {
    case 60:
      r = 255;
      g = 0;
      b = 0;
      break;

   case 61:
      r = 0;
      g = 0;
      b = 255;
      break;
 
    case 62:
      r = 255;
      g = 255;
      b = 255;
      break;

    case 63: //green
      r = 119;
      g = 244;
      b = 66;
 
    default:
      break;   
  }

  for(int i=0;i<NUMPIXELS;i++){

    pixels.setPixelColor(i, pixels.Color(r,g,b)); // Moderately bright green color.
    pixels.setBrightness((velocity * 2) + 1 );
    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
    // Do something when the note is released.
    // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
  for(int i=0;i<NUMPIXELS;i++){


    pixels.setPixelColor(i, pixels.Color(0,0,0));

    pixels.show(); // This sends the updated pixel color to the hardware.
  }
}

// -----------------------------------------------------------------------------

void setup()
{
    //Serial.begin(9600);
    pixels.begin();
    
    // Connect the handleNoteOn function to the library,
    // so it is called upon reception of a NoteOn.
    MIDI.setHandleNoteOn(handleNoteOn);  // Put only the name of the function

    // Do the same for NoteOffs
    MIDI.setHandleNoteOff(handleNoteOff);

    // Initiate MIDI communications, listen to all channels
    MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop()
{
    // Call MIDI.read the fastest you can for real-time performance.
    MIDI.read();

    // There is no need to check if there are messages incoming
    // if they are bound to a Callback function.
    // The attached method will be called automatically
    // when the corresponding message has been received.
}
