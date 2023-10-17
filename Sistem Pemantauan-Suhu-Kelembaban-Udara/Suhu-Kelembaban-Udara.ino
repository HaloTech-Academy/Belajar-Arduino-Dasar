//Library LCD I2C
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27,16,2);

// Include the libraries:
#include <Adafruit_Sensor.h>
#include <DHT.h>

// Set DHT pin:
#define DHTPIN 7

// Set DHT type, uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

// Initialize DHT sensor for normal 16mhz Arduino:
DHT dht = DHT(DHTPIN, DHTTYPE);

void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);

  // Setup sensor:
  dht.begin();
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0,0);
  lcd.print("Suhu: "); // 7

  lcd.setCursor(0,1);
  lcd.print("Kelemb.: "); //13
}

void loop() {
  // Wait a few seconds between measurements:
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)

  // Read the humidity in %:
  float h = dht.readHumidity();
  // Read the temperature as Celsius:
  float t = dht.readTemperature();
  // Read the temperature as Fahrenheit:
  float f = dht.readTemperature(true);

  lcd.setCursor(6,0);
  lcd.print(t);
  lcd.setCursor(10,0);
  lcd.print((char)223);
  lcd.setCursor(11,0);
  lcd.print("C");

  lcd.setCursor(9,1);
  lcd.print(h);
  lcd.setCursor(15,1);
  lcd.print("%");

  // Check if any reads failed and exit early (to try again):
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Fahrenheit (default):
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius:
  float hic = dht.computeHeatIndex(t, h, false);


  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" % ");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" \xC2\xB0");
  Serial.print("C | ");
  
}
