#include <Encoder.h>
#include <Control_Surface.h>
#include <Keyboard.h>


const int save = 16;
const int quit = 8;
const int marker = 6;
const int tonePin = 3;
const int pauze = 15;

USBMIDI_Interface usbmidi;

NoteButtonLatching BF[] = {
  {14,  MCU::REWIND},
  {9,   MCU::FAST_FWD}
};

NoteButton Transport[] = {
   //{14,  MCU::REWIND},
  //{9,   MCU::FAST_FWD},
  //{15,  MCU::STOP},
  {7,   MCU::RECORD},
  //{15,   MCU::PLAY}
};

NoteValueLED leds[] = {
  {10,  MCU::RECORD}
 };

void setup() {
  Control_Surface.begin();
  pinMode(save, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(pauze, INPUT_PULLUP);
}

void loop() { // Refresh all inputs
  Control_Surface.loop();

  if (digitalRead(save) == LOW){
    Keyboard.press(131);
    Keyboard.press(129);
    Keyboard.press('s');
    delay(200);
    Keyboard.releaseAll();}

    if (digitalRead(quit) == LOW){
    Keyboard.press(131);
    Keyboard.press(129);
    Keyboard.press('w');
    delay(200);
    Keyboard.releaseAll();}

    if (digitalRead(pauze) == LOW){
    Keyboard.write(32);
    delay(200);}

    if (digitalRead(marker) == LOW){
    //Keyboard.write(176);
    tone(tonePin, 500, 50);
    delay(125);
    tone(tonePin, 500, 50);
    delay(200);
    noTone(tonePin);
    }
}
