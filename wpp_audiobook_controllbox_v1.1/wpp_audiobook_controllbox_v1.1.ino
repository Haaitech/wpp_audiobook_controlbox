#include <USB-MIDI.h>
#include <Keyboard.h>
//#include <Control_Surface.h>

const int save    = 16;
const int quit    = 8;
const int marker  = 6;
const int tonePin = 3;
const int pauze   = 15;
const int rev     = 14;
const int fwd     = 9;
const int rec     = 7;
const int led     = 10;
bool isplaying    = false;

byte ping[]         = {0x90, 0x00, 0x00};
byte selectzone[]   = {0xB0, 0x0F, 0x0E};
byte revon[]        = {0xB0, 0X2F, 0x41};
byte revoff[]       = {0xB0, 0X2F, 0x01};
byte fwdon[]        = {0xB0, 0X2F, 0x42};
byte fwdoff[]       = {0xB0, 0X2F, 0x02};
byte stopon[]       = {0xB0, 0X2F, 0x43};
byte stopoff[]      = {0xB0, 0X2F, 0x03};
byte playon[]       = {0xB0, 0X2F, 0x44};
byte playoff[]      = {0xB0, 0X2F, 0x04};
byte recon[]        = {0xB0, 0X2F, 0x45};
byte recoff[]       = {0xB0, 0X2F, 0x05};

#define DRE(signal, state) (state=(state<<1)|signal)==B00001111
byte revRisingState;
byte fwdRisingState;
byte pauzeRisingState;
byte recRisingState;

#define DFE(signal, state) (state=(state<<1)|signal)==B11110000
byte revFallingState;
byte fwdFallingState;
byte pauzeFallingState;
byte recFallingState;


USBMIDI_CREATE_DEFAULT_INSTANCE();
unsigned long t0 = millis();

void setup() {
  MIDI.begin(1);
  //Serial.begin(9600);
  pinMode(save, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(pauze, INPUT_PULLUP);
  pinMode(rec, INPUT_PULLUP);
  pinMode(fwd, INPUT_PULLUP);
  pinMode(rev, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() { // Refresh all inputs

  MIDI.read();

  if ((millis() - t0) > 1000){
    t0 = millis();
    MIDI.sendSysEx(3, ping, true);
  }
  

  if (digitalRead(save) == LOW){
    Keyboard.press(131);
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

//Read the transport buttons and send corresponding sysex array's

    if (DFE(digitalRead(rev), revFallingState)) {
        MIDI.sendSysEx(3, selectzone, true);
        delay(20);
        MIDI.sendSysEx(3, revon, true);
    }

    if (DRE(digitalRead(rev), revRisingState)) {
        MIDI.sendSysEx(3, selectzone, true);
        delay(20);
        MIDI.sendSysEx(3, revoff, true);
    }

    if (DFE(digitalRead(fwd), fwdFallingState)) {
        MIDI.sendSysEx(3, selectzone, true);
        delay(20);
        MIDI.sendSysEx(3, fwdon, true);
    }

    if (DRE(digitalRead(fwd), fwdRisingState)) {
       MIDI.sendSysEx(3, selectzone, true);
       delay(20);
       MIDI.sendSysEx(3, fwdoff, true);
    }

    if (DFE(digitalRead(rec), recFallingState)) {
        MIDI.sendSysEx(3, selectzone, true);
        delay(20);
        MIDI.sendSysEx(3, recon, true);
    }

    if (DRE(digitalRead(rec), recRisingState)) {
       MIDI.sendSysEx(3, selectzone, true);
       delay(20);
       MIDI.sendSysEx(3, recoff, true);
    }

     if (DFE(digitalRead(pauze), pauzeFallingState)) {
        MIDI.sendSysEx(3, selectzone, true);
        delay(20);
        MIDI.sendSysEx(3, playon, true);
    }

    if (DRE(digitalRead(pauze), pauzeRisingState)) {
       MIDI.sendSysEx(3, selectzone, true);
       delay(20);
       MIDI.sendSysEx(3, playoff, true);
    }
}
