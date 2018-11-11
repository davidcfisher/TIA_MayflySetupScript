/**************************************************************************


**************************************************************************/

// Arduion libraries
#include <Arduino.h>
#include <Wire.h>                // I2C communicaions
#include "Sodaq_DS3231.h"        // Real Time Clock
#include <SDL_Arduino_SSD1306.h> // OLED Display, 1 of 2
#include <AMAdafruit_GFX.h>      // OLED Display, 2 of 2

// TIA libraries
#include <TIA_dateTimeFunctions.h> // date and time functions

int State8 = LOW;
int State9 = LOW;

float degF;
float degC;

int LEDtime = 2000; //milliseconds

// Create an instance of the OLED display
SDL_Arduino_SSD1306 oled(4); // FOR OLED via I2C, reset pin 4

void setup()
{
  // OLED SSD1306 Init
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, false); // initialize with the I2C addr 0x3C (for the 128x64)

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(3);
  oled.setTextColor(WHITE);
  oled.print("CKPT 1");
  oled.display();

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();

  Serial.println("Cellular 2G");
  Serial.println("Modified by Dave 11/11/18");
}

void loop()
{

  if (State8 == LOW)
  {
    State8 = HIGH;
  }
  else
  {
    State8 = LOW;
  }

  digitalWrite(8, State8);
  State9 = !State8;
  digitalWrite(9, State9);

  //DateTime now = rtc.now(); //get the current date-time

  char suffix[] = ": ";
  serialPrint_dateTime(suffix);

  rtc.convertTemperature();    // convert current temperature into registers
  degC = rtc.getTemperature(); // read registers
  degF = degC * 1.8 + 32;      // calculate °F
  Serial.print(degC, 1);
  Serial.print("° C, ");
  Serial.print(degF, 1);
  Serial.println("° F");

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.println("CKPT 2");
  oled.setTextSize(1);
  oledPrint_dateTime(oled, "", true);
  oled.print(degF, 1);
  oled.println(" degF");
  oled.display();

  delay(LEDtime);
}
