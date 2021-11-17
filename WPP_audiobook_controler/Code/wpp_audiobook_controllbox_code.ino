#include <Keyboard.h>

const int save = 16;
const int rev = 14;
const int fwd = 9;
const int quit = 8;
const int pauze = 15;
const int rec = 7;
const int marker = 6;
const int tonePin = 3;
const int led = 10;

void setup() {
  
  pinMode(save, INPUT_PULLUP);
  pinMode(rev, INPUT_PULLUP);
  pinMode(fwd, INPUT_PULLUP);
  pinMode(quit, INPUT_PULLUP);
  pinMode(pauze, INPUT_PULLUP);
  pinMode(rec, INPUT_PULLUP);
  pinMode(marker, INPUT_PULLUP);
  pinMode(led, OUTPUT);


}

void loop() {
  
  if (digitalRead(save) == LOW){
    }
    
  if (digitalRead(rev) == LOW){
    Keyboard.write(97);}
    
  if (digitalRead(fwd) == LOW){
    Keyboard.write(98);}
    
  if (digitalRead(quit) == LOW){
    Keyboard.press(131);
    Keyboard.press(129);
    Keyboard.press('w');
    delay(100);
    Keyboard.releaseAll();}
    
  if (digitalRead(pauze) == LOW){
    Keyboard.write(32);}
    
  if (digitalRead(rec) == LOW){
    Keyboard.write(99);}

  if (digitalRead(marker) == LOW){
    //Keyboard.write(176);
    tone(tonePin, 500, 50);
    delay(125);
    tone(tonePin, 500, 50);
    delay(200);
    noTone(tonePin);
    }

}
