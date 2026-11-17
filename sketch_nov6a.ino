#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

Servo spinguy;   // King's face
Servo servo2;    // Platform
Servo servo3;    // Unused for now

SoftwareSerial mySerial(11, 9);  // RX, TX
DFRobotDFPlayerMini player;

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  spinguy.attach(10);
  servo2.attach(12);
  servo3.attach(13);

  Serial.begin(9600);
  mySerial.begin(9600);

  if (player.begin(mySerial)) {
    Serial.println("Check one: CLEAR");
  } else {
    Serial.println("Check one: FAIL");
  }

  player.volume(25);
}

void loop() {

  // Platform servo slowly spins
  servo2.write(100);

  // King's facial expression animation
  spinguy.write(180);
  delay(825);

  spinguy.write(90);
  delay(3000);

  spinguy.write(0);
  delay(825);

  spinguy.write(90);
  delay(3000);

  // Button 1 (Pin 2)
  // Plays Jester (#3) then King (#4)
  if (digitalRead(2) == LOW) {

    player.play(3);   // Jester
    delay(6000);      // wait for audio #3

    player.play(4);   // King
    delay(6000);      // wait for audio #4

    while (digitalRead(2) == LOW);
    delay(100);
  }

  // Button 2 (Pin 4)
  if (digitalRead(4) == LOW) {

    player.play(2);

    while (digitalRead(4) == LOW);
    delay(100);
  }
}
