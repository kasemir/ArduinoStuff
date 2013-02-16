// LM34 Temperature Measurement
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

// LM34 Pinout: +, signal, Gnd

// LM34 signal on analog input 0
// Serial monitor to see temperature

#define INFO 13

#include "LM34.h"

LM34 temp(DEFAULT_LM34);

void setup()
{
    Serial.begin(9600);
    Serial.println("LM34 Temperature");
    delay(2000);
    
    pinMode(INFO, OUTPUT);
    digitalWrite(INFO, 1);
}


void loop()
{
    Serial.print("Temperature: ");
    Serial.print(temp.degC());
    Serial.println(" C");
    delay(1000);
}
