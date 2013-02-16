// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include <SoftwareSerial.h>
#include "SerialLCD.h"

SerialLCD lcd(DEFAULT_LCD);

void setup()
{
    Serial.begin(9600);
    Serial.println("\nSerial LCD Demo");

    // lcd.backlight(15);
    lcd.clear();

    lcd.print("Welcome!");
    lcd.set(16);
    lcd.print("to the LCD");
    delay(2000);

    lcd.backlight(30);
    delay(2000);
    lcd.backlight(15);
    delay(2000);

    lcd.clear();
    lcd.print("Line ");
    lcd.print(1);
    lcd.set(16);
    lcd.print("Line ");
    lcd.print(2);
    delay(2000);

    lcd.clear();
}

void loop()
{
    lcd.scroll(millis()/300);
    lcd.scroll(",");
    delay(300);
}
