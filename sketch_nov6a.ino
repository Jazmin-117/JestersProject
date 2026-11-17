#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
#include <Servo.h>

Servo spinguy;   // King's face
Servo servo2;    // Platform
Servo servo3;    // Automatic action servo

SoftwareSerial mySerial(11, 9);  // RX, TX
DFRobotDFPlayerMini player;

// Variables for servo3 sequence
int turnStage = 0;
unsigned long lastTurn = 0;

void setup() {

  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);

  spinguy.attach(10);
  servo2.attach(12);
  servo3.attach(13);

  servo3.write(90);   // stop continuous servo

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

  // Servo3 automatic one-revolution sequence
  if (turnStage == 0) {
    servo3.write(180);
    delay(500);
    servo3.write(90);
    lastTurn = millis();
    turnStage = 1;
  }

  if (turnStage == 1 && millis() - lastTurn >= 1000) {
    servo3.write(180);
    delay(500);
    servo3.write(90);
    lastTurn = millis();
    turnStage = 2;
  }

  if (turnStage == 2 && millis() - lastTurn >= 1000) {
    servo3.write(180);
    delay(500);
    servo3.write(90);
    lastTurn = millis();
    turnStage = 3;
  }

  if (turnStage == 3 && millis() - lastTurn >= 1000) {
    servo3.write(180);
    delay(500);
    servo3.write(90);
    turnStage = 4;   // Finished
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
}
