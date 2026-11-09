#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

Servo spinguy;

SoftwareSerial mySerial(11, 9); //this says that tx and rx are conected to 11 and 9
DFRobotDFPlayerMini player;


void setup() {

pinMode(2, INPUT_PULLUP); // this sets the arduinos built in resistors for the buttons (also the buttons must start low for this)
pinMode(4, INPUT_PULLUP);

spinguy.attach(10);

Serial.begin(9600);
mySerial.begin(9600);

if (player.begin(mySerial)){
  Serial.println("Check one: CLEAR");
}else{
  Serial.println("Check one: FAIL"); // check to see if working
}

player.volume(25);

}

void loop() {
  spinguy.write(180);
if (digitalRead(2) == LOW){
  player.play(1); // plays audio one (the audio's name is 0001.mp3)
  while(digitalRead(2) == LOW); // this makes it so you only press the button once and it will play the full audio, if you press another button whle this plays it will switch to that or start over.
  delay(100);
}
if (digitalRead(4) == LOW){
  player.play(2); // plays audio 2 (the audio's name is 0002.mp3)
  while(digitalRead(4) == LOW);
  delay(100);

 
}

}
