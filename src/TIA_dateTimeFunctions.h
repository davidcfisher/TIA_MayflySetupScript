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
void oledPrint_ckpt(SDL_Arduino_SSD1306 oled, int ckpt)
{

    oled.clearDisplay();
    oled.setCursor(0, 0);
    oled.setTextSize(2);
    oled.setTextColor(WHITE);
    oled.print("CKPT ");
    oled.println(ckpt);
    oled.display();
}

void greenLED(String state, int flashes = 3)
{
    if (state == "on")
    {
        digitalWrite(8, HIGH);
    }
    if (state == "off")
    {
        digitalWrite(8, LOW);
    }
    if (state == "flash")
    {
        for (int i = 0; i < flashes; i++)
        {
            greenLED("on");
            delay(50);
            greenLED("off");
            delay(50);
        }
    }
}
void redLED(String state, int flashes = 3)
{
    if (state == "on")
    {
        digitalWrite(9, HIGH);
    }
    if (state == "off")
    {
        digitalWrite(9, LOW);
    }
    if (state == "flash")
    {
        for (int i = 0; i < flashes; i++)
        {
            redLED("on");
            delay(50);
            redLED("off");
            delay(50);
        }
    }
}
void showOnlyLED(String color)
{
    if (color == "red")
    {
        redLED("on");
        greenLED("off");
    }
    if (color == "green")
    {
        greenLED("on");
        redLED("off");
    }
}