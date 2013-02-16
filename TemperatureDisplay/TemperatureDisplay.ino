// Display temperature (min, max, current)
// on 2x16 LCD:
//
//             111111
//   0123456789012345
//  "T  : 19.83 C    "
//  "Rng: 19.83 19.83"
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.
#include <SoftwareSerial.h>
#include <SerialLCD.h>
#include <LM34.h>

LM34 temp(DEFAULT_LM34);
SerialLCD lcd(DEFAULT_LCD);

float min, max;

void setup()
{
    Serial.begin(9600);
    Serial.println("Temperature Monitor");
    
    lcd.clear();
    lcd.print("T  : ??.?? C    ");
    lcd.set(16);
    lcd.print("Rng: ??.?? ??.??");
    delay(1000);
    min = max = temp.degC();
}

char buf[16];

void loop()
{
    float deg_c = temp.degC();
    if (deg_c < min)
        min = deg_c;
    if (deg_c > max)
        max = deg_c;
  
    dtostrf(deg_c, 6, 2, buf);
    lcd.set(4);
    lcd.print(buf);

    dtostrf(min, 6, 2, buf);
    lcd.set(16+4);
    lcd.print(buf);

    dtostrf(max, 6, 2, buf);
    // lcd.set(16+10);
    lcd.print(buf);

    delay(2000);
}
