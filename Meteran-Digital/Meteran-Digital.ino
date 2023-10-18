#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int trigPin = 2; // Pin Trig sensor ultrasonik
const int echoPin = 3; // Pin Echo sensor ultrasonik

LiquidCrystal_I2C lcd(34, 16, 2); // Inisialisasi LCD I2C dengan alamat 0x27

void setup() {
  lcd.init(); // Inisialisasi LCD
  lcd.backlight(); // Nyalakan pencahayaan latar belakang

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Meteran Digital");
  delay(1000);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  int cm = (duration / 2) / 29.1;

  lcd.setCursor(0, 1);
  lcd.print("Panjang: ");
  lcd.print(cm);
  lcd.print(" cm     ");

  delay(1000); // Perbarui layar LCD setiap detik
}
