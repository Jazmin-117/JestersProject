#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS 2

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
int baselineTemp = 0;
int celsius = 0;

const int ledPin = 13;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 sensors.begin();

pinMode(2, INPUT);
pinMode(ledPin, OUTPUT);
digitalWrite(2, LOW);
digitalWrite(ledPin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
baselineTemp = 30;

//celsius = map(((analogRead(2) - 30) * 3.04), 0, 1023, -40, 125);
celsius = sensors.getTempCByIndex(0);
Serial.print(celsius);
Serial.println(" C, ");

if (celsius < baselineTemp){
  digitalWrite(ledPin, LOW);
Serial.print(celsius < baselineTemp);
}else{
  digitalWrite(ledPin, HIGH);
}


sensors.requestTemperatures();

  

  //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print("°C  |  ");

  //print the temperature in Fahrenheit
  Serial.print((sensors.getTempCByIndex(0) * 9.0) / 5.0 + 32.0);
  Serial.println("°F");

  delay(500);
}
