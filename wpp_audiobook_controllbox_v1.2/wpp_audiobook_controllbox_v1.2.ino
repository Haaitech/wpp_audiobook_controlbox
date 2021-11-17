//#include <USB-MIDI.h>
#include <Keyboard.h>
#include <Control_Surface.h>

USBMIDI_Interface midi;


const int save = 16;
const int quit = 8;
const int marker = 6;
Button  tonePin {3};
Button  pauze   {15};
Button  rev     {14};
Button  fwd     {9};
Button  rec     {7};
const int led = 10;
bool isplaying = false;

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



unsigned long t0 = millis();

void setup() {
  //Serial.begin(9600);
  rev.begin();
  fwd.begin();
  rec.begin();
  pauze.begin();// enables internal pull-up
  midi.begin();
  pinMode(save, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() { // Refresh all inputs

  midi.update();

  if ((millis() - t0) > 1000){
    t0 = millis();
    midi.sendSysEx(ping);
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

    //if (digitalRead(marker) == LOW){
    //tone(tonePin, 500, 50);
    //delay(125);
    //tone(tonePin, 500, 50);
    //delay(200);
    //noTone(tonePin);
    //}

//Read the transport buttons and send corresponding sysex array's

    if (rev.update() == Button::Falling){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(revon);
    }

    if (rev.update() == Button::Rising){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(revoff);
    }

    if (fwd.update() == Button::Falling){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(fwdon);
    }

    if (fwd.update() == Button::Rising){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(fwdoff);
    }

    if (rec.update() == Button::Falling){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(recon);
    }

    if (rec.update() == Button::Rising){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(recoff);
    }

    if (pauze.update() == Button::Falling){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(stopon);
    }

    if (pauze.update() == Button::Rising){
    midi.sendSysEx(selectzone);
    midi.sendSysEx(stopoff);
    }

}
