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

// Mayfly configuration
#define greenLED_pin 8
#define redLED_pin 9

// Create an instance of the OLED display
SDL_Arduino_SSD1306 oled(4); // FOR OLED via I2C, reset pin 4

//============ TinyGSM START
/**************************************************************
 *
 * TinyGSM Getting Started guide:
 *   http://tiny.cc/tiny-gsm-readme
 *
 * NOTE:
 * Some of the functions may be unavailable for your modem.
 * Just comment them out.
 *
 **************************************************************/

// specify modem for TinyGSM
//#define TINY_GSM_MODEM_SIM800
#define TINY_GSM_MODEM_XBEE

// Include TinyGSM for the modem
// This include must be included below the define of the modem name!
#include <TinyGsmClient.h>

 // Set the serial port for the modem - software serial can also be used.
////HardwareSerial &ModemSerial = Serial1;

// Create a variable for the modem baud rate - this will be used in the begin function for the port
////const long ModemBaud = 9600;

// Create a new TinyGSM modem to run on that serial port and return a pointer to it
////TinyGsm *tinyModem = new TinyGsm(ModemSerial);

// Create a new TCP client on that modem and return a pointer to it
////TinyGsmClient *tinyClient = new TinyGsmClient(*tinyModem);







////////////////////////////////////////////////

// Set serial for debug console (to the Serial Monitor, speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1

// or Software Serial on Uno, Nano
//#include <SoftwareSerial.h>
//SoftwareSerial SerialAT(2, 3); // RX, TX

//#define DUMP_AT_COMMANDS
#define TINY_GSM_DEBUG SerialMon

// Set phone numbers, if you want to test SMS and Calls
#define SMS_TARGET "+570-724-2119"
//#define CALL_TARGET "+380xxxxxxxxx"

// Your GPRS credentials
// Leave empty, if missing user or pass
const char apn[] = "YourAPN";
const char user[] = "";
const char pass[] = "";

#include <TinyGsmClient.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
//============ TinyGSM END

void setup()
{
  // Set console baud rate
  SerialMon.begin(115200);
  delay(10);

  // OLED SSD1306 Init
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C, false); // initialize with the I2C addr 0x3C (for the 128x64)

  oledPrint_ckpt(oled, 94);

  pinMode(greenLED_pin, OUTPUT);
  pinMode(redLED_pin, OUTPUT);

  //Serial.begin(115200);
  Wire.begin();
  rtc.begin();

  Serial.println("Cellular 2G");
  Serial.println("Modified by Dave 11/14/18");

  // Set your reset, enable, power pins here
  delay(3000);
  oledPrint_ckpt(oled, 109);
  // Set GSM module baud rate
  TinyGsmAutoBaud(SerialAT);
  oledPrint_ckpt(oled, 112);
}

void loop()
{
  oledPrint_ckpt(oled, 115);
  showOnlyLED("green");
  greenLED("flash");
  greenLED("on");
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  DBG("Initializing modem...");
  if (!modem.init())
  {
    oledPrint_ckpt(oled, 121);
    showOnlyLED("red");
    redLED("flash",10);
    redLED("on");
    delay(10000);
    oledPrint_ckpt(oled, 124);

    return;
  }
  oledPrint_ckpt(oled, 128);

  String modemInfo = modem.getModemInfo();
  DBG("Modem:", modemInfo);

  // Unlock your SIM card with a PIN
  //modem.simUnlock("1234");

  DBG("Waiting for network...");
  if (!modem.waitForNetwork())
  {
    delay(10000);
    return;
  }

  if (modem.isNetworkConnected())
  {
    DBG("Network connected");
  }

  DBG("Connecting to", apn);
  if (!modem.gprsConnect(apn, user, pass))
  {
    delay(10000);
    return;
  }

  bool res = modem.isGprsConnected();
  DBG("GPRS status:", res ? "connected" : "not connected");

  String ccid = modem.getSimCCID();
  DBG("CCID:", ccid);

  String imei = modem.getIMEI();
  DBG("IMEI:", imei);

  String cop = modem.getOperator();
  DBG("Operator:", cop);

  IPAddress local = modem.localIP();
  DBG("Local IP:", local);

  int csq = modem.getSignalQuality();
  DBG("Signal quality:", csq);

  // This is NOT supported on M590
  ////int battLevel = modem.getBattPercent();
  ////DBG("Battery lavel:", battLevel);

  // This is only supported on SIMxxx series
  #ifdef TINY_GSM_MODEM_SIM800
  float battVoltage = modem.getBattVoltage() / 1000.0F;
  DBG("Battery voltage:", battVoltage);
  #endif

  // This is only supported on SIMxxx series
  #ifdef TINY_GSM_MODEM_SIM800
  String gsmLoc = modem.getGsmLocation();
  DBG("GSM location:", gsmLoc);
  #endif

  // This is only supported on SIMxxx series
  #ifdef TINY_GSM_MODEM_SIM800
  String gsmTime = modem.getGSMDateTime(DATE_TIME);
  DBG("GSM Time:", gsmTime);
  String gsmDate = modem.getGSMDateTime(DATE_DATE);
  DBG("GSM Date:", gsmDate);
  #endif

  ////String ussd_balance = modem.sendUSSD("*111#");
  ////DBG("Balance (USSD):", ussd_balance);

  ////String ussd_phone_num = modem.sendUSSD("*161#");
  ////DBG("Phone number (USSD):", ussd_phone_num);

#if defined(TINY_GSM_MODEM_SIM808)
  modem.enableGPS();
  String gps_raw = modem.getGPSraw();
  modem.disableGPS();
  DBG("GPS raw data:", gps_raw);
#endif

#if defined(SMS_TARGET)
  res = modem.sendSMS(SMS_TARGET, String("Hello from ") + imei);
  DBG("SMS:", res ? "OK" : "fail");

  // This is only supported on SIMxxx series
  #ifdef TINY_GSM_MODEM_SIM800
  res = modem.sendSMS_UTF16(SMS_TARGET, u"Привіііт!", 9);
  DBG("UTF16 SMS:", res ? "OK" : "fail");
  #endif
#endif

#if defined(CALL_TARGET)
  DBG("Calling:", CALL_TARGET);

  // This is NOT supported on M590
  res = modem.callNumber(CALL_TARGET);
  DBG("Call:", res ? "OK" : "fail");

  if (res)
  {
    delay(1000L);

    // Play DTMF A, duration 1000ms
    modem.dtmfSend('A', 1000);

    // Play DTMF 0..4, default duration (100ms)
    for (char tone = '0'; tone <= '4'; tone++)
    {
      modem.dtmfSend(tone);
    }

    delay(5000);

    res = modem.callHangup();
    DBG("Hang up:", res ? "OK" : "fail");
  }
#endif

  modem.gprsDisconnect();
  if (!modem.isGprsConnected())
  {
    DBG("GPRS disconnected");
  }
  else
  {
    DBG("GPRS disconnect: Failed.");
  }

  // Try to power-off (modem may decide to restart automatically)
  // To turn off modem completely, please use Reset/Enable pins
  modem.poweroff();
  DBG("Poweroff.");

  // Do nothing forevermore
  while (true)
  {
    modem.maintain();
  }
}
