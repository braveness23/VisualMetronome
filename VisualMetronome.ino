#include <MIDI.h>
#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 40

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

MIDI_CREATE_DEFAULT_INSTANCE();

void handleNoteOn(byte channel, byte note, byte velocity)
{
  int r = 0;
  int g = 0;
  int b = 0;

  int pitch = note % 12;

  switch (pitch)
  {
  // C - Red
  case 0:
    r = 255;
    g = 0;
    b = 0;
    break;

  // C# - Blue
  case 1:
    r = 0;
    g = 0;
    b = 255;
    break;

  // D - White
  case 2:
    r = 255;
    g = 255;
    b = 255;
    break;

  // D# - Apple Green
  case 3:
    r = 14;
    g = 194;
    b = 114;
    break;
    
  // E - Canary Yellow
  case 4:
    r = 254;
    g = 241;
    b = 28;
    break;
    
      // F - Pumpkin Orange
  case 5:
    r = 240;
    g = 129;
    b = 70;
    break;

  default:
    break;
  }

  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.setBrightness((velocity * 2) + 1);
  pixels.show(); // This sends the updated pixel color to the hardware.
}

void handleNoteOff(byte channel, byte pitch, byte velocity)
{
  // Do something when the note is released.
  // Note that NoteOn messages with 0 velocity are interpreted as NoteOffs.
  for (int i = 0; i < NUMPIXELS; i++)
  {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
}

// -----------------------------------------------------------------------------

void setup()
{
  //Serial.begin(9600);
  pixels.begin();

  // First let's test the LEDs by "playing" MIDI notes 0 thru 11"
  // This gives a some feedback that the hardware is all working
  for (int i = 0; i < 12; i++)
  {
    handleNoteOn(0, i, 127);
    delay(250);
    handleNoteOff(0, i, 0);
  }

  // Connect the handleNoteOn function to the library,
  // so it is called upon reception of a NoteOn.
  MIDI.setHandleNoteOn(handleNoteOn); // Put only the name of the function

  // Connect the handleNoteOff function to the library,
  // so it is called upon reception of a NoteOff.
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
