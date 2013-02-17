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

// C or F?
#define CELSIUS

static LM34 temp(DEFAULT_LM34);
static SerialLCD lcd(DEFAULT_LCD);
static float deg, min, max;

void setup()
{
    Serial.begin(9600);
    Serial.println("Temperature Monitor");
    
    lcd.clear();
    lcd.print("TempMon 0.1");
    delay(2000);
    lcd.clear();

#ifdef CELSIUS
    lcd.print("T  : ??.?? C    ");
#else
    lcd.print("T  : ??.?? F    ");
#endif
    lcd.set(16);
    lcd.print("Rng: ??.?? ??.??");
    delay(1000);
    
    // Set initial values
    deg = min = max = temp.degC();
}

char buf[16];

void loop()
{
#ifdef CELSIUS
    float n_deg = temp.degC();
#else
    float n_deg = temp.degF();
#endif
    // Smoothly update displayed value
    deg = deg * 0.9 + n_deg*0.1;
    // Min, Max
    if (deg < min)
        min = deg;
    if (deg > max)
        max = deg;
  
    dtostrf(deg, 6, 2, buf);
    lcd.set(4);
    lcd.print(buf);

    dtostrf(min, 6, 2, buf);
    lcd.set(16+4);
    lcd.print(buf);

    dtostrf(max, 6, 2, buf);
    // lcd.set(16+10);
    lcd.print(buf);

    delay(5000);
}
