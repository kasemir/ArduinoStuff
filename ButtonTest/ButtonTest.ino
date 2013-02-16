// Read BUTTON, mirrow via built-in INFO LED
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#define BUTTON 12
#define INFO 13

void setup()
{
    Serial.begin(9600);    
    Serial.println("Button Test");
    Serial.println("INFO LED lit: input HIGH");
    Serial.println("INFO LED off: input LOW");
    pinMode(BUTTON, INPUT);
    pinMode(INFO, OUTPUT);
}

void loop()
{
    digitalWrite(INFO, digitalRead(BUTTON));
}
