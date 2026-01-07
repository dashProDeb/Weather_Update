#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// ------------------ DHT CONFIG ------------------
#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// ------------------ OLED CONFIG ------------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ------------------ TIMER CONFIG ------------------
hw_timer_t *timer = NULL;
volatile bool sleepFlag = false;

// ------------------ DEEP SLEEP CONFIG ------------------
#define uS_TO_S_FACTOR 1000000ULL
#define SLEEP_TIME 25   // seconds

// ------------------ TIMER ISR ------------------
void IRAM_ATTR onTimer() {
  sleepFlag = true;
}

void setup() {
  Serial.begin(115200);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  float h = dht.readHumidity();
  float t = dht.readTemperature();

  display.setCursor(0, 0);
  display.println("ESP32 Weather");

  if (isnan(h) || isnan(t)) {
    display.println("Sensor Error");
  } else {
    display.print("Temp: ");
    display.print(t);
    display.println(" C");

    display.print("Humidity: ");
    display.print(h);
    display.println(" %");
  }

  display.display();

  // -------- ESP32 TIMER (CORE v3.x) --------
  timer = timerBegin(1000000);          // 1 MHz = 1 µs tick
  timerAttachInterrupt(timer, &onTimer);
  timerAlarm(timer, 5000000, false, 0); // 2 seconds, no repeat
  timerStart(timer);
}

void loop() {
  if (sleepFlag) {
    display.clearDisplay();
    display.display();

    Serial.println("Going to deep sleep...");
    esp_sleep_enable_timer_wakeup((uint64_t)SLEEP_TIME * uS_TO_S_FACTOR);
    esp_deep_sleep_start();
  }
}
