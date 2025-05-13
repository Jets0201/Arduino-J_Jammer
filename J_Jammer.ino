/*
  Jets made "J_J"
*/

#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include <ezButton.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET     Null
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RF24 radio(2, 4);//CE, CSN
ezButton A(Null);
ezButton B(Null);
ezButton UP(Null);

const int wifiFrequencies[] = {
  2412,
  2417,
  2422,
  2427,
  2432,
  2437,
  2442,
  2447,
  2452,
  2457,
  2462
};

const char* modes[] = {
  "BLE & All 2.4 GHz",
  "Just Wi-Fi",
};
uint8_t mode = 0;
bool ismode = false;

void fullAttack() {
  for (size_t i = 0; i < 80; i++) {
    radio.setChannel(i);
  }
}
void wifiAttack() {
  for (int i = 0; i < sizeof(wifiFrequencies) / sizeof(wifiFrequencies[0]); i++) {
    radio.setChannel(wifiFrequencies[i] - 2400);
  }
}
  
void mode_change() {
  UP.loop();
  A.loop(); // OK
  B.loop(); // Cancel

  if (UP.isPressed()) {
    if (mode == 2) { // mode change
      mode = 0;
    }else {
      mode++;
    }
  }
  if (A.isPressed()) { // mode on/off
    ismode = !ismode;
  }
}

void mode_show() {
  if (ismode) {
    // attck
    
  }else {
    // menu
    
  }
}

void mode_attack() {
  if (ismode) {
     switch (mode) {
       case 0:
         // BLE & All 2.4 GHz
         
         fullAttack();
         break();
       
       case 1:
         // Just Wi-Fi
         
         wifiAttack();
         break();
  }
}

void setup() {
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
}

void loop() {
  mode_change();
  mode_show();
  mode_attack();
}
