// TIA date and time functions

#include "Sodaq_DS3231.h" // Real Time Clock

void serialPrint_dateTime(char suffix[])
{

    DateTime now = rtc.now(); //get the current date-time

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
    Serial.print(suffix);
}
void oledPrint_dateTime(SDL_Arduino_SSD1306 oled, int textSize, char suffix[], bool newLine = false)
{

    DateTime now = rtc.now(); //get the current date-time
    oled.setTextSize(textSize);
    oled.print(now.month());
    oled.print('/');
    oled.print(now.date());
    oled.print('/');
    oled.println(String(now.year()).substring(2));
    oled.print(' ');
    oled.print(now.hour());
    oled.print(':');
    oled.print(now.minute());
    oled.print(':');
    oled.print(now.second());

    if (newLine)
    {
        //Serial.println("newLine detected!");
        oled.println(suffix);
    }
    else
    {
        oled.print(suffix);
    }

    //oled.display();
}