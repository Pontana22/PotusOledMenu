#include <PotusOledMenu.h>

#define ledNum 5 // number of leds
#define upPin 2
#define downPin 3
#define selectPin 4

PotusOledMenu menu;

char labels[ledNum][18] = { "Light 1", "Light 2", "Light 3", "Light 4", "Light 5" }; // array with labels, second dimension has to be 18

// 16x16px .xbm bitmaps generated using convertio.co
const unsigned char lightbulbOff[] PROGMEM = {
  0x00, 0x00, 0xC0, 0x01, 0x30, 0x06, 0x08, 0x08, 0x08, 0x08, 0x84, 0x10, 
  0x44, 0x11, 0x24, 0x12, 0x48, 0x09, 0x48, 0x09, 0x50, 0x05, 0xE0, 0x03, 
  0x20, 0x02, 0xE0, 0x03, 0x20, 0x02, 0xC0, 0x01, };

const unsigned char lightbulbOn[] PROGMEM = {
  0xFF, 0xFF, 0x3F, 0xFE, 0x0F, 0xF8, 0x07, 0xF0, 0x07, 0xF0, 0x83, 0xE0, 
  0x43, 0xE1, 0x23, 0xE2, 0x47, 0xF1, 0x47, 0xF1, 0x4F, 0xF9, 0x1F, 0xFC, 
  0xDF, 0xFD, 0x1F, 0xFC, 0xDF, 0xFD, 0x3F, 0xFE, };

unsigned char* icons[ledNum] = { lightbulbOff, lightbulbOff, lightbulbOff, lightbulbOff, lightbulbOff }; // pointer array with icons

bool ledStates[ledNum] = { 0, 0, 0, 0, 0 }; // array with led-states

const int ledPins[ledNum] = { 8, 9, 10, 11, 12 }; // array with led pin numbers

void setup() {
  pinMode(upPin, INPUT);
  pinMode(downPin, INPUT);
  pinMode(selectPin, INPUT);

  menu.begin();
  menu.config(ledNum, 1, 1, 1, 1, 0, 1); // configure options
  menu.labels(labels); // set labels
  menu.icons(icons); // set icons
  menu.draw(); // display the menu
}

void loop() {
  if (digitalRead(upPin)) {
    menu.up();
    delay(100);
  }
  else if (digitalRead(downPin)) {
    menu.down();
    delay(100);
  }
  else if (digitalRead(selectPin)) {
    toggleLed(menu.getSelected());
  }
}

void toggleLed(int led) {
  ledStates[led] = ledStates[led] ? 0 : 1; // toggle the selected item led state
  digitalWrite(ledPins[led], ledStates[led]); // toggle the selected led
  icons[led] = ledStates[led] ? lightbulbOn : lightbulbOff; // toggle the selected item icon
  menu.setIcon(led, icons[led]); // apply the new icon
}
