#include <Control_Surface.h>
#include <Keyboard.h>

const int save    = 16;
const int quit    = 8;
const int marker  = 6;
const int tonePin = 3;
const int pauze   = 15;
const int rec     = 7;
bool isplaying    = false;
bool isRecording  = false;


// Setup variables for detecting falling or rising state of the buttons without interupt (the Atmega 32U4 does not have enough interupt pins to make this work without this workaround)
#define DRE(signal, state) (state=(state<<1)|signal)==B00001111
byte pauzeRisingState;
byte recRisingState;


#define DFE(signal, state) (state=(state<<1)|signal)==B11110000
byte pauzeFallingState;
byte recFallingState;

// Initialize USB midi interface
USBMIDI_Interface usbmidi;

// These are the rev and fwd buttons, they are disabled for now because of a bug in protools 10,
// uncomment the next two lines to enable them.

//CCButton REV {14, {MIDI_CC::PR_REV, CHANNEL_1}};  
//CCButton FWD {9, {MIDI_CC::PR_FWD, CHANNEL_1}};

CCLED led { 10,  MIDI_CC::PR_REC}; // Rec indicator led
CCLED checkplay { 5, MIDI_CC::PR_PLAY}; // This is a not conected pin but will be set to high if playing, used for some logic do not disable.

void setup() {
  Keyboard.begin();
  Control_Surface.begin();
  pinMode(save, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(pauze, INPUT_PULLUP);
  pinMode(rec, INPUT_PULLUP);

}

boolean readButtons() {

  // Read button states every 5 ms (debounce time):
  static unsigned long lastDebounce;
  if (millis() - lastDebounce >= 5) {
    lastDebounce = millis();

    // Check if rec button is pushed
    if (DFE(digitalRead(rec), recFallingState)) {
      // If recording is started change rec button functionality to pause.
      if (isRecording == true){
        Control_Surface.sendControlChange(0x74, 127);
      } else {
        Control_Surface.sendControlChange(0x76, 127);
        Control_Surface.sendControlChange(0x75, 127);
      }
    }

    // Check if rec button is released
    if (DRE(digitalRead(rec), recRisingState)) {
      // If recording is started change rec button functionality to pause.
      if(isRecording == true){
        // Cleanup midi by sending note off command
        Control_Surface.sendControlChange(0x74, 0);
        Control_Surface.sendControlChange(0x75, 0);
        Control_Surface.sendControlChange(0x76, 0);
      } else {
        // Cleanup midi by sending note off command
        Control_Surface.sendControlChange(0x76, 0);
        Control_Surface.sendControlChange(0x75, 0);
      }
    }

    // Check if pause button is pressed
    if (DFE(digitalRead(pauze), pauzeFallingState))  {
      // If audio is playing send stop command if pressed.
      if (isplaying == true) {
        Control_Surface.sendControlChange(0x74, 127);
      } else { // Send play command if pressed.
        Control_Surface.sendControlChange(0x75, 127);
      }
    }
    // Check if pause button is released.
    if (DRE(digitalRead(pauze), pauzeRisingState)) {
      // Cleanup midi by sending note off command
      Control_Surface.sendControlChange(0x74, 0);
      Control_Surface.sendControlChange(0x75, 0);
    }
  }
}

void loop() { // Refresh all inputs

  Control_Surface.loop();

  // Logic for isPlaying and isRecording

  if (digitalRead(5) == HIGH) {
    isplaying = true;
  } else {
    isplaying = false;
  }

  if (digitalRead(10) == HIGH) {
    isRecording = true;
  } else {
    isRecording = false;
  }

  // Check if save button is pressed
  if (digitalRead(save) == LOW) {
    Keyboard.press(131);
    //Keyboard.press(129);
    Keyboard.press('s');
    delay(200);
    Keyboard.releaseAll();
  }

  // Check if quit button is pressed
  if (digitalRead(quit) == LOW) {
    Keyboard.press(131);
    Keyboard.press(129);
    Keyboard.press('w');
    delay(200);
    Keyboard.releaseAll();
  }

  // Check if marker button is pressed
  if (digitalRead(marker) == LOW) {
    tone(tonePin, 500, 50);
    delay(125);
    tone(tonePin, 500, 50);
    delay(200);
    noTone(tonePin);
  }

  readButtons();
}
