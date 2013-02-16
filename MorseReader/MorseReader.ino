// Morse Code Reader
//
// Copyright 2011 by Kay Kasemir. All Rights Reserved.

// Button in input 12, powered via 10k from 13,
// grounding input 12 when pressed.
// Or using tone detector on input 12.
// 
// Built-in LED on output 13.

#define BUTTON_VOLTAGE 11
#define BUTTON 12
#define INFO 13

#include "KeyMonitor.h"
#include "MorseDecoder.h"

void setup()
{
    Serial.begin(9600);
    Serial.println("Morse Decoder");

    // Provide voltage to button
    pinMode(BUTTON_VOLTAGE, OUTPUT);
    digitalWrite(BUTTON_VOLTAGE, HIGH);

    // Prepare to read button and show result on INFO
    pinMode(BUTTON, INPUT);
    pinMode(INFO, OUTPUT);
} 

static KeyMonitor key_monitor;
static MorseDecoder decoder;

void loop()
{
    // Read key
    const boolean keydown = !digitalRead(BUTTON);
    // Mirror on LED
    digitalWrite(INFO, keydown);
    // Handle key state
    char c = key_monitor.handleKey(keydown);
    switch (c)
    {
    case DIT:
    case DAH:
        decoder.add(c);
        // Serial.print(c);
        break;
    case END_OF_CHAR:
        Serial.print(decoder.decode());
        break;
    case END_OF_WORD:
        Serial.print(' ');
        break;
    }
}

