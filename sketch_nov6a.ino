#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

Servo spinguy;
Servo servo2;
Servo servo3;

SoftwareSerial mySerial(11, 9);  // RX, TX
DFRobotDFPlayerMini player;

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  spinguy.attach(10);
  servo2.attach(12);
  servo3.attach(13);

  servo3.write(0);   // starting position

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

  // First two servos continuously spin
  spinguy.write(180); // full/normal speed
  servo2.write(100); // slower speed

  // Button 1
  if (digitalRead(2) == LOW) {

    servo3.write(180);   // raise object
    player.play(1);      // play 0001.mp3

    delay(6000);         // wait for audio to finish

    servo3.write(0);     // lower object

    while (digitalRead(2) == LOW);
    delay(100);
  }

  // Button 2
  if (digitalRead(4) == LOW) {

    servo3.write(180);   // raise object
    player.play(2);      // play 0002.mp3

    delay(6000);         // wait for audio to finish

    servo3.write(0);     // lower object

    while (digitalRead(4) == LOW);
    delay(100);
  }
}
