#include <Control_Surface.h>
#include <Keyboard.h>

const int save = 16;
const int quit = 8;
const int marker = 6;
const int tonePin = 3;
const int pauze = 15;
const int rev = 14;
const int fwd = 9;
bool isplaying = false;

#define DFE(signal, state) (state=(state<<1)|signal)==B00001111

byte revRisingState;
byte fwdRisingState;

USBMIDI_Interface usbmidi;

NoteButton Transport[] = {
  {14,  MCU::REWIND},
  {9,   MCU::FAST_FWD},
  {7,   MCU::RECORD},
};

NoteLED led { 10,  MCU::RECORD};
NoteLED checkplay { 5, MCU::PLAY};

void setup() {
  Control_Surface.begin();
  pinMode(save, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(pauze, INPUT_PULLUP);

  const MIDIAddress note = MIDI_Notes::C(4);
  const uint8_t velocity = 127;                
}

void loop() { // Refresh all inputs
  
  Control_Surface.loop();

  if (digitalRead(5) == HIGH){
    isplaying = true;
  }else{
    isplaying = false;
  }

  if (digitalRead(save) == LOW){
    Keyboard.press(131);
    //Keyboard.press(129);
    Keyboard.press('s');
    delay(200);
    Keyboard.releaseAll();
    }

    if (digitalRead(quit) == LOW){
    Keyboard.press(131);
    Keyboard.press(129);
    Keyboard.press('w');
    delay(200);
    Keyboard.releaseAll();
    }

    if (digitalRead(marker) == LOW){
    tone(tonePin, 500, 50);
    delay(125);
    tone(tonePin, 500, 50);
    delay(200);
    noTone(tonePin);
    }

    if ((digitalRead(pauze) == LOW && digitalRead(10) == HIGH) || 
       (digitalRead(pauze) == LOW && isplaying == true)){
      usbmidi.sendNoteOn(93, 127);
      delay(100);
      usbmidi.sendNoteOff(93, 127);
      delay(100);
      isplaying = false;
    }
    
    if (digitalRead(pauze) == LOW && isplaying == false){
      usbmidi.sendNoteOn(94, 127);
      delay(100);
      usbmidi.sendNoteOff(94, 127);
      delay(100);
      isplaying = true;
    }

     if (DFE(digitalRead(rev), revRisingState)) {
      usbmidi.sendNoteOn(93, 127);
      delay(100);
      usbmidi.sendNoteOff(93, 127);
      delay(100);
      isplaying = false;  
    }

     if (DFE(digitalRead(fwd), fwdRisingState)) {
      usbmidi.sendNoteOn(93, 127);
      delay(100);
      usbmidi.sendNoteOff(93, 127);
      delay(100);
      isplaying = false;  
    }
}
