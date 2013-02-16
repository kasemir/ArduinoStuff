// Persistence-of-Vision stuff
//
// Copyright 2011 by Kay Kasemir. All Rights Reserved.

// LEDs on outputs 3...10.
// 
// BUTTON_VOLTAGE 11 connected via 10k to BUTTON 12.
// BUTTON grounds input 12 when pressed.
// 
// Built-in INFO LED on output 13 used to indicate when BUTTON is pressed.
// 
// 3050 bytes

#include "POVBits.h"

#define BUTTON_VOLTAGE 11
#define BUTTON 12
#define INFO 13

// Output pin assignments for LEDs
#define LEDs 8
static byte led[] = { 10, 9, 8, 7, 6, 5, 4, 3 };
 
// Delay between characters
#define DELAY 1

static const char *texts[] =
{
    "Hi   ",
    HEART "   ",
    EPICS "   ",
    SMILEY " ",
};

static int mode = 0;

static POVBits pov_bits;

void setup()
{
    Serial.begin(9600);
    // Set LEDs to output
    for (int i=0; i<LEDs; ++i)
        pinMode(led[i], OUTPUT);

    // Provide voltage to button
    pinMode(BUTTON_VOLTAGE, OUTPUT);
    digitalWrite(BUTTON_VOLTAGE, HIGH);
    // Prepare to read button and show result on INFO
    pinMode(BUTTON, INPUT);
    pinMode(INFO, OUTPUT);

    // Check of LED power, sequence of LED hookup
    knightRider();
    sequenceAllOn();
        
    pov_bits.setText(texts[mode]);
} 


void loop()
{
    // Update LEDs to next line (column) of character bits
    const byte b = pov_bits.getNextBits();
    byte mask = 0x01;
    for (int i=0; i<LEDs; ++i)
    {
        digitalWrite(led[i], (b & mask) != 0);
        mask <<= 1;
    }
    delay(DELAY);

    // Switch 'mode', i.e. between text1, text2
    if (digitalRead(BUTTON) == 0)
    {
        digitalWrite(INFO, 1);
        while (digitalRead(BUTTON) == 0)
            delay(10);
        digitalWrite(INFO, 0);
        ++mode;
        if (mode >= (sizeof(texts) / sizeof(texts[0])))
            mode = 0;
        pov_bits.setText(texts[mode]);
    }
}

// Blink all LEDs
static void blinkAll()
{
   for (int i=0; i<LEDs; ++i)
    {
        digitalWrite(led[i], HIGH);
        delay(100);
        digitalWrite(led[i], LOW);
    }
}
 
// Sequence all 'on'
static void sequenceAllOn()
{
    for (int i=0; i<LEDs; ++i)
    {
        digitalWrite(led[i], HIGH);
        delay(100);
    }
    delay(150);
    for (int i=0; i<LEDs; ++i)
        digitalWrite(led[i], LOW);
}


// Knight rider right/left/right
static void knightRider()
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

