#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// Pin untuk sensor ultrasonik
const int trigPin = 2;
const int echoPin = 3;

// Pin untuk servo motor
const int servoPin = 4;
Servo myservo;

// Inisialisasi LCD
LiquidCrystal_I2C lcd(34,16, 2);

void setup() {
  // Menginisialisasi servo motor
  myservo.attach(servoPin);

  // Menginisialisasi sensor ultrasonik
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Inisialisasi komunikasi I2C
  Wire.begin();

  // Inisialisasi LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(5, 0);
  lcd.print("Status: ");
}

void loop() {
  // Membaca jarak dari sensor ultrasonik
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Menghitung jarak dalam sentimeter

  // Menggerakkan servo jika ada objek dalam jarak tertentu
  if (distance < 15) { // Ubah nilai sesuai dengan jarak yang diinginkan
    openLid();
  } else {
    closeLid();
  }
}

void openLid() {
  myservo.write(90); // Menggerakkan servo untuk membuka penutup
  lcd.setCursor(0, 1);
  lcd.print("  Tong Terbuka   ");
}

void closeLid() {
  myservo.write(0); // Menggerakkan servo untuk menutup penutup
  lcd.setCursor(0, 1);
  lcd.print("  Tong Tertutup  ");
}
