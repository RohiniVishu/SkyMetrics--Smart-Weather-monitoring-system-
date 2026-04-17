#define BLYNK_TEMPLATE_ID "ID"
#define BLYNK_TEMPLATE_NAME "NAME"
#define BLYNK_AUTH_TOKEN "TOKEN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP280.h>
#include <DHT.h>

// WiFi
const char* ssid = "WIFI_NAME";
const char* pwd  = "PASSWORD";

// Sensors
DHT dht(4, DHT22);
Adafruit_BMP280 bmp;

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// LED
int ledPin = 5;

// Timing
unsigned long previousMillis = 0;
const long interval = 2000;

// LCD switching
unsigned long lcdMillis = 0;
const long lcdInterval = 2000;
bool showFirstScreen = true;

// Blynk state
int manualState = 0;

// Sensor values (store globally)
float humidity, temp, pressure;

void setup() {
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pwd);

  Wire.begin(21, 22);

  dht.begin();

  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 not found!");
    while (1);
  }

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Weather System");
  delay(1000);   // small startup delay is fine
  lcd.clear();

  pinMode(13, INPUT);
  pinMode(ledPin, OUTPUT);
}

// Blynk button
BLYNK_WRITE(V0) {
  manualState = param.asInt();
  if(manualState==1){
    digitalWrite(ledPin,HIGH);
  }
  else{
    digitalWrite(ledPin,LOW);
  }
}

void loop() {
  Blynk.run();

  unsigned long currentMillis = millis();

  // ========= SENSOR READ =========
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    humidity = dht.readHumidity();
    temp = dht.readTemperature();
    pressure = bmp.readPressure() / 100.0;

    Serial.println("------ DATA ------");
    Serial.print("Temp: "); Serial.println(temp);
    Serial.print("Humidity: "); Serial.println(humidity);
    Serial.print("Pressure: "); Serial.println(pressure);
    Serial.println("------------------");

    // LED logic
    if (temp > 35) {
      digitalWrite(ledPin, HIGH);
    } else {
      digitalWrite(ledPin, manualState ? HIGH : LOW);
    }
  }

  // ========= LCD SWITCHING (NON-BLOCKING) =========
  if (currentMillis - lcdMillis >= lcdInterval) {
    lcdMillis = currentMillis;
    showFirstScreen = !showFirstScreen;

    lcd.clear();

    if (showFirstScreen) {
      // Screen 1
      if (digitalRead(13) == 0) {
        lcd.setCursor(0, 0);
        lcd.print("Sunny");
      } else {
        lcd.setCursor(0, 0);
        lcd.print("Cloudy");
      }

      lcd.setCursor(0, 1);
      lcd.print("T:");
      lcd.print(temp, 1);
      lcd.print(" H:");

      if (!isnan(humidity)) {
        lcd.print(humidity, 0);
      } else {
        lcd.print("Err");
      }

    } else {
      // Screen 2
      lcd.setCursor(0, 0);
      lcd.print("Pressure:");
      lcd.setCursor(0, 1);
      lcd.print(pressure);
    }
  }
}