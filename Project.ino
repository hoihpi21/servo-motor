#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);


int trigPin = 32;    // TRIG pin
int echoPin = 33;    // ECHO pin

int Slot = 4;

Servo myservo1;

void setup() {

  lcd.begin(16,2);`
  lcd.backlight();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  
  myservo1.attach(3);
  myservo1.write(100);

  lcd.setCursor(0, 0);
  lcd.print(" IoT ");
  lcd.setCursor(0, 1);
  lcd.print(" PARKING SYSTEM ");
  delay(2000);
  lcd.clear();
}

void loop() {
  // generate 10-microsecond pulse to TRIG pin
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // measure duration of pulse from ECHO pin
  float duration_us = pulseIn(echoPin, HIGH);

  // calculate the distance in cm
  float distance_cm = duration_us * 0.017;

  // Check if space is available based on distance measured
  if (distance_cm > 10 && Slot > 0) {
    myservo1.write(0);
    Slot--;
    delay(1000); // Delay to ensure the vehicle is parked properly
  } else {
    lcd.setCursor(0, 0);
    lcd.print(" SORRY ");
    lcd.setCursor(0, 1);
    lcd.print(" Parking Full ");
    delay(2000);
    lcd.clear();
  }

  lcd.setCursor(0, 0);
  lcd.print(" WELCOME! ");
  lcd.setCursor(0, 1);
  lcd.print("Slot Left: ");
  lcd.print(Slot);
}
