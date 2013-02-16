// LED Bar Demo
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.
#include "LEDBar.h"

// LEDs

// Some 0..5V signal on INPUT
#define INPUT 0

LEDBar led_bar(3, 4, 5, 6, 7, 8, 9,10);

void setup()
{
    Serial.begin(9600);    
    Serial.println("LED Bar Demo");
    
    led_bar.knightRider();
} 


void loop()
{
    int level = analogRead(0);
    int secs = millis() / 1000;
    if ((secs / 4) % 2 == 1)
      led_bar.level(level);
    else
      led_bar.bar(level);  
}

