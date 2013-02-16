// LED Bar
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include "LEDBar.h"

// Output pin assignments for LEDs
byte LEDBar::led[] = { 10, 9, 8, 7, 6, 5, 4, 3 };
#define LEDs 8

LEDBar::LEDBar()
{
    init();
}

LEDBar::LEDBar(int led0, ...)
{
    va_list args;
    va_start(args, led0);
    led[0] = led0;
    for (int i=1; i<LEDs; ++i)
        led[i] = va_arg(args, int);
    init();
}

void LEDBar::init()
{
    for (int i=0; i<LEDs; ++i)
        pinMode(led[i], OUTPUT);
}  

// Knight rider right/left/right
void LEDBar::knightRider()
{
    for (int i=0; i<LEDs; ++i)
    {
        digitalWrite(led[i], HIGH);
        delay(40);
        digitalWrite(led[i], LOW);
    }
    for (int i=LEDs-1; i>=0; --i)
    {
        digitalWrite(led[i], HIGH);
        delay(40);
        digitalWrite(led[i], LOW);
    }
}

void LEDBar::bar(int level)
{
    // Map 0...1023 to number of LEDs
    const int count = (unsigned long)LEDs * level / 1023L;
    for (int i=0; i<LEDs; ++i)
        digitalWrite(led[i], i <= count ? HIGH : LOW);
}

void LEDBar::level(int level)
{
    // Map 0...1023 to individual LED
    const int index = (unsigned long)LEDs * level / 1023L;
    for (int i=0; i<LEDs; ++i)
        digitalWrite(led[i], i == index ? HIGH : LOW);
}

