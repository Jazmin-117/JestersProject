#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

Servo spinguy;   // King's face
Servo servo2;    // Platform
Servo servo3;    // Cage

SoftwareSerial mySerial(11, 9);  // RX, TX
DFRobotDFPlayerMini player;

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  spinguy.attach(10);
  servo2.attach(12);
  servo3.attach(13);

  servo3.write(0);

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

  // Platform servo runs continuously
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

  // Button 1
  if (digitalRead(2) == LOW) {

    servo3.write(180);   // raise cage
    player.play(1);

    delay(6000);

    servo3.write(0);     // lower cage

    while (digitalRead(2) == LOW);
    delay(100);
  }

  // Button 2
  if (digitalRead(4) == LOW) {

    servo3.write(180);   // raise cage
    player.play(2);

    delay(6000);

    servo3.write(0);     // lower cage

    while (digitalRead(4) == LOW);
    delay(100);
  }
}
