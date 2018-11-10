/**************************************************************************


**************************************************************************/

#include <Arduino.h>
#include <Wire.h>                   // I2C communicaions
#include "Sodaq_DS3231.h"           // Real Time Clock
#include <SDL_Arduino_SSD1306.h>    // OLED Display, 1 of 2
#include <AMAdafruit_GFX.h>         // OLED Display, 2 of 2
#include <SPI.h>                    // For SPI comm (needed for not getting compile error)

// Pin definitions
#define OLED_RESET_PIN  4           // OLED display reset pin

// Display demo definitions
//#define NUMFLAKES 10
//#define XPOS 0
//#define YPOS 1
//#define DELTAY 2
//#define LOGO16_GLCD_HEIGHT 16
//#define LOGO16_GLCD_WIDTH  16

int State8 = LOW;
int State9 = LOW;

float degF;
float degC;

int LEDtime = 2000;   //milliseconds

// reset the OLED
SDL_Arduino_SSD1306 display(OLED_RESET_PIN); // FOR OLED via I2C

void setup () {

  pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    Serial.begin(115200);
    Wire.begin();
    rtc.begin();

    Serial.println("OLED test");
    Serial.println("Modified by Dave 11/10/18");

    // START ===============================================================================================

  // SSD1306 Init

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false);  // initialize with the I2C addr 0x3C (for the 128x64)
  
  display.stopscroll();
  display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.println("CKPT 1");
  display.display();
}

void loop ()
{
    if (State8 == LOW) {
      State8 = HIGH;
    } else {
      State8 = LOW;
    }
    digitalWrite(8, State8);
    State9 = !State8;
    digitalWrite(9, State9);

    DateTime now = rtc.now(); //get the current date-time

    Serial.print("DCF: ");
    Serial.print(now.month());
    Serial.print('/');
    Serial.print(now.date());
    Serial.print('/');
    Serial.print(String(now.year()).substring(2));
    Serial.print(' ');
    Serial.print(now.hour());
    Serial.print(':');
    Serial.print(now.minute());
    Serial.print(':');
    Serial.print(now.second());
    Serial.print(": ");
    
    rtc.convertTemperature();             // convert current temperature into registers
    degC = rtc.getTemperature();          // read registers
    degF = degC * 1.8 + 32;               // calculate °F
    Serial.print(degC,1);
    Serial.print("° C, ");
    Serial.print(degF,1);
    Serial.println("° F");

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(0,0);
    display.print(now.month());
    display.print('/');
    display.print(now.date());
    display.print('/');
    display.println(String(now.year()).substring(2));
    display.print(now.hour());
    display.print(':');
    display.print(now.minute());
    display.print(':');
    display.println(now.second());
    display.print(degF,1);
    display.println(" degrees F");
    display.display();

    delay(LEDtime);
}
