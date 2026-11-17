#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

Servo spinguy;   // King's face
Servo servo2;    // New 180° servo
Servo servo3;    // Platform (360° servo)

SoftwareSerial mySerial(11, 9);  // RX, TX
DFRobotDFPlayerMini player;

// Platform sequence variables
bool platformDone = false;

void setup() {

  pinMode(2, INPUT_PULLUP);  // Button 1
  pinMode(4, INPUT_PULLUP);  // Button 2
  pinMode(7, INPUT_PULLUP);  // Button 3
  pinMode(6, INPUT_PULLUP);  // Button 4

  spinguy.attach(10);
  servo2.attach(12);
  servo3.attach(13);

  servo2.write(0);    // Start position
  servo3.write(90);   // Stop platform servo

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

  // King's facial expression animation
  spinguy.write(180);
  delay(825);

  spinguy.write(90);
  delay(3000);

  spinguy.write(0);
  delay(825);

  spinguy.write(90);
  delay(3000);

  // Platform turns slowly 3 times with pauses, then stops
  if (!platformDone) {

    servo3.write(100);
    delay(400);

    servo3.write(90);
    delay(1000);

    servo3.write(100);
    delay(400);

    servo3.write(90);
    delay(1000);

    servo3.write(100);
    delay(400);

    servo3.write(90);

    platformDone = true;
  }

  // Button 1: Jester (#3) then King (#4)
  if (digitalRead(2) == LOW) {

    player.play(3);
    delay(6000);

    player.play(4);
    delay(6000);

    while (digitalRead(2) == LOW);
    delay(100);
  }

  // Button 2: King's laughter (#5)
  if (digitalRead(4) == LOW) {

    player.play(5);

    while (digitalRead(4) == LOW);
    delay(100);
  }

  // Button 3: Move servo2 to 90° + play laughter (#5)
  if (digitalRead(7) == LOW) {

    servo2.write(90);
    player.play(5);

    while (digitalRead(7) == LOW);
    delay(100);
  }

  // Button 4: Play laughter (#5)
  if (digitalRead(6) == LOW) {

    player.play(5);

    while (digitalRead(6) == LOW);
    delay(100);
  }
}
