//Library LCD I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd (34,16, 2);

int buzzer=4;
int ledMerah=5;
int ledKuning=6;
int ledHijau=7;

int soilMoisturePin = A0; // Pin analog untuk sensor kelembapan tanah

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  
  pinMode(buzzer,OUTPUT);
  pinMode(ledMerah,OUTPUT);
  pinMode(ledKuning,OUTPUT);
  pinMode(ledHijau,OUTPUT);

}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin); // Membaca nilai sensor

  Serial.print("Nilai Kelembapan Tanah: ");
  Serial.print(soilMoistureValue);

  // Konversi nilai kelembapan menjadi persentase (jika diperlukan)
  float soilMoisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);
  Serial.print(" - Persentase: ");
  Serial.print(soilMoisturePercentage);
  Serial.println("%");
  
  lcd.setBacklight(1);
  lcd.setCursor(0,0);
  lcd.print("Soil Moist: ");
  lcd.setCursor(11,0);
  lcd.print(soilMoisturePercentage);
  lcd.setCursor(15,0);
  lcd.print("%");
  
  if(soilMoisturePercentage<50){
  lcd.setCursor(1,1);
  lcd.print("Kelemb. Rendah");
  digitalWrite(ledMerah,HIGH);
  digitalWrite(ledKuning,LOW);
  digitalWrite(ledHijau,LOW);
  digitalWrite(buzzer,HIGH);
  delay(1000);
  }
  
  else if(soilMoisturePercentage<75){
  lcd.setCursor(1,1);
  lcd.print("Kelemb. Cukup ");
  digitalWrite(ledMerah,LOW);
  digitalWrite(ledKuning,HIGH);
  digitalWrite(ledHijau,LOW);
  digitalWrite(buzzer,LOW);
  delay(1000);
  }

  else{
  lcd.setCursor(1,1);
  lcd.print("Kelemb. Tinggi ");
  digitalWrite(ledMerah,LOW);
  digitalWrite(ledKuning,LOW);
  digitalWrite(ledHijau,HIGH);
  digitalWrite(buzzer,LOW);
  delay(1000);
  }

  delay(1000); // Tunggu 1 detik sebelum membaca ulang
}
