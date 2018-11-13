/**************************************************************************


**************************************************************************/

// Arduino libraries
#include <Arduino.h>
#include <Wire.h>                // I2C communicaions
#include "Sodaq_DS3231.h"        // Real Time Clock
#include <SDL_Arduino_SSD1306.h> // OLED Display, 1 of 2
#include <AMAdafruit_GFX.h>      // OLED Display, 2 of 2

// PlatformIO libraries
#include <String.h>

// TIA libraries
#include <TIA_dateTimeFunctions.h> // date and time functions

int ckpt = 1;
String ckptStr;

int State8 = LOW;
int State9 = LOW;

float degF;
float degC;

int LEDtime = 2000; //milliseconds

// Create an instance of the OLED display
SDL_Arduino_SSD1306 oled(4); // FOR OLED via I2C, reset pin 4

//======= TINYGSM Start
/**************************************************************
 *
 * For this example, you need to install PubSubClient library:
 *   https://github.com/knolleary/pubsubclient
 *   or from http://librarymanager/all#PubSubClient
 *
 * TinyGSM Getting Started guide:
 *   http://tiny.cc/tiny-gsm-readme
 *
 * For more MQTT examples, see PubSubClient library
 *
 **************************************************************
 * Use Mosquitto client tools to work with MQTT
 *   Ubuntu/Linux: sudo apt-get install mosquitto-clients
 *   Windows:      https://mosquitto.org/download/
 *
 * Subscribe for messages:
 *   mosquitto_sub -h test.mosquitto.org -t GsmClientTest/init -t GsmClientTest/ledStatus -q 1
 * Toggle led:
 *   mosquitto_pub -h test.mosquitto.org -t GsmClientTest/led -q 1 -m "toggle"
 *
 * You can use Node-RED for wiring together MQTT-enabled devices
 *   https://nodered.org/
 * Also, take a look at these additional Node-RED modules:
 *   node-red-contrib-blynk-ws
 *   node-red-dashboard
 *
 **************************************************************/

// Select your modem:
#define TINY_GSM_MODEM_SIM800
// #define TINY_GSM_MODEM_SIM808
// #define TINY_GSM_MODEM_SIM900
// #define TINY_GSM_MODEM_UBLOX
// #define TINY_GSM_MODEM_BG96
// #define TINY_GSM_MODEM_A6
// #define TINY_GSM_MODEM_A7
// #define TINY_GSM_MODEM_M590
// #define TINY_GSM_MODEM_ESP8266
// #define TINY_GSM_MODEM_XBEE

#include <TinyGsmClient.h>
#include <PubSubClient.h>

// Set serial for debug console (to the Serial Monitor, default speed 115200)
#define SerialMon Serial

// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// or Software Serial on Uno, Nano
//#include <SoftwareSerial.h>
//SoftwareSerial SerialAT(2, 3); // RX, TX

// Your GPRS credentials
// Leave empty, if missing user or pass
const char apn[] = "apn.konekt.io";
const char user[] = "";
const char pass[] = "";

// MQTT details
const char *broker = "test.mosquitto.org";

const char *topicLed = "GsmClientTest/led";
const char *topicInit = "GsmClientTest/init";
const char *topicLedStatus = "GsmClientTest/ledStatus";

TinyGsm modem(SerialAT);
TinyGsmClient client(modem);
PubSubClient mqtt(client);

#define LED_PIN 13
int ledStatus = LOW;

long lastReconnectAttempt = 0;

//======= TINYGSM End

void setup()
{
  // OLED SSD1306 Init
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, false); // initialize with the I2C addr 0x3C (for the 128x64)

  oled.clearDisplay();
  oled.setCursor(0, 0);
  oled.setTextSize(3);
  oled.setTextColor(WHITE);
  auto ckptStr = std::to_string(ckpt);
  oled.print(ckptStr);
  oled.print(ckpt);
  oled.display();

  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  Serial.begin(115200);
  Wire.begin();
  rtc.begin();

  Serial.println("Cellular 2G");
  Serial.println("Modified by Dave 11/13/18");
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

  delay(LEDtime);
}
