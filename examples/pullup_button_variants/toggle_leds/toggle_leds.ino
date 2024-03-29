/*
  toggle_leds.ino

  Example sketch showcasing practical use of a simple menu

  Author: Pontus Martinsson
  Created: 2024-02-15
  Last modified: 2024-02-16

  For more information, visit: https://github.com/Pontana22/PotusOledMenu

  License: MIT License

  Copyright (c) 2024 Pontus Martinsson

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

#include <PotusOledMenu.h>

#define ledNum 5 // number of leds
#define upPin 2
#define downPin 3
#define selectPin 4

PotusOledMenu menu;

char* labels[ledNum] = { "Light 1", "Light 2", "Light 3", "Light 4", "Light 5" }; // array with labels, second dimension has to be 18

// 16x16px .xbm bitmaps generated using convertio.co
const unsigned char lightbulbOff[] PROGMEM = {
  0x00, 0x00, 0xC0, 0x01, 0x30, 0x06, 0x08, 0x08, 0x08, 0x08, 0x84, 0x10, 
  0x44, 0x11, 0x24, 0x12, 0x48, 0x09, 0x48, 0x09, 0x50, 0x05, 0xE0, 0x03, 
  0x20, 0x02, 0xE0, 0x03, 0x20, 0x02, 0xC0, 0x01, };

const unsigned char lightbulbOn[] PROGMEM = {
  0x00, 0x00, 0xC0, 0x01, 0xF0, 0x07, 0xF8, 0x0F, 0xF8, 0x0F, 0x7C, 0x1F, 
  0xBC, 0x1E, 0xDC, 0x1D, 0xB8, 0x0E, 0xB8, 0x0E, 0xB0, 0x06, 0xE0, 0x03, 
  0x20, 0x02, 0xE0, 0x03, 0x20, 0x02, 0xC0, 0x01, };

unsigned char* icons[ledNum] = { lightbulbOff, lightbulbOff, lightbulbOff, lightbulbOff, lightbulbOff }; // pointer array with icons

bool ledStates[ledNum] = { 0, 0, 0, 0, 0 }; // array with led-states
const int ledPins[ledNum] = { 8, 9, 10, 11, 12 }; // array with led pin numbers

bool buttonPressed = false;

void setup() {
  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(selectPin, INPUT_PULLUP);

  // set all led pins to output
  for (int i = 0; i < ledNum; i++) {
    pinMode(ledPins[i], OUTPUT);
  }

  menu.begin();
  menu.config(ledNum, 1, 1, 1, 1, 0, 1); // configure options
  menu.labels(labels); // set labels
  menu.icons(icons); // set icons
  menu.draw(); // display the menu
}

// read buttons and apply changes accordingly
void loop() {
  bool upPressed = digitalRead(upPin);
  bool downPressed = digitalRead(downPin);
  bool selectPressed = digitalRead(selectPin);

  if (!(upPressed) && !(buttonPressed)) { // up
    buttonPressed = true;
    menu.up();
  }
  else if (!(downPressed) && !(buttonPressed)) { // down
    buttonPressed = true;
    menu.down();
  }
  else if (!(selectPressed) && !(buttonPressed)) { // select
    buttonPressed = true;
    toggleLed(menu.getSelected());
  }
  else if (buttonPressed && upPressed && downPressed && selectPressed) { // reset buttonPressed when no button is pressed
    buttonPressed = false;
  }
}

// toggle everything
void toggleLed(int led) {
  ledStates[led] = ledStates[led] ? 0 : 1; // toggle the selected item led state
  digitalWrite(ledPins[led], ledStates[led]); // toggle the selected led
  icons[led] = ledStates[led] ? lightbulbOn : lightbulbOff; // toggle the selected item icon
  menu.setIcon(led, icons[led]); // apply the new icon
  menu.draw(); // refresh menu
}
