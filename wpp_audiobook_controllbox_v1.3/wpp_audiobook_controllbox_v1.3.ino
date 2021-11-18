#include <Control_Surface.h>
#include <Keyboard.h>

const int save    = 16;
const int quit    = 8;
const int marker  = 6;
const int tonePin = 3;
const int pauze   = 15;
const int rec     = 7;
bool isplaying    = false;

#define DRE(signal, state) (state=(state<<1)|signal)==B00001111
byte pauzeRisingState;
byte recRisingState;

#define DFE(signal, state) (state=(state<<1)|signal)==B11110000
byte pauzeFallingState;
byte recFallingState;

USBMIDI_Interface usbmidi;


CCButton REV {14, {MIDI_CC::PR_REV, CHANNEL_1}};
CCButton FWD {9, {MIDI_CC::PR_FWD, CHANNEL_1}};
//CCButton STP {15, {MIDI_CC::PR_STOP, CHANNEL_1}};
//CCButton PLY {7, {MIDI_CC::PR_PLAY, CHANNEL_1}};
//CCButton REC {7, {MIDI_CC::PR_REC, CHANNEL_1}};

CCLED led { 10,  MIDI_CC::PR_REC};
CCLED checkplay { 5, MIDI_CC::PR_PLAY};

void setup() {
  Control_Surface.begin();
  pinMode(save, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(pauze, INPUT_PULLUP);
  pinMode(rec, INPUT_PULLUP);

}

void loop() { // Refresh all inputs

  Control_Surface.loop();

  if (digitalRead(5) == HIGH) {
    isplaying = true;
  } else {
    isplaying = false;
  }

  if (digitalRead(save) == LOW) {
    Keyboard.press(131);
    //Keyboard.press(129);
    Keyboard.press('s');
    delay(200);
    Keyboard.releaseAll();
  }

  if (digitalRead(quit) == LOW) {
    Keyboard.press(131);
    Keyboard.press(129);
    Keyboard.press('w');
    delay(200);
    Keyboard.releaseAll();
  }

  if (digitalRead(marker) == LOW) {
    tone(tonePin, 500, 50);
    delay(125);
    tone(tonePin, 500, 50);
    delay(200);
    noTone(tonePin);
  }

  if (DFE(digitalRead(rec), recFallingState)) {
    Control_Surface.sendControlChange(0x76, 127);
    Control_Surface.sendControlChange(0x75, 127);
  }

  if (DRE(digitalRead(rec), recRisingState)) {
    Control_Surface.sendControlChange(0x76, 0);
    Control_Surface.sendControlChange(0x75, 0);
  }

  if (DFE(digitalRead(pauze), pauzeFallingState))  {
    if (isplaying == true) {
      Control_Surface.sendControlChange(0x74, 127);
    } else {
      Control_Surface.sendControlChange(0x75, 127);
    }
  }

}
