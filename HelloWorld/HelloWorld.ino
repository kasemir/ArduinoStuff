// Basic Getting-Started check for new board
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

// Serial monitor to see startup message
// Built-in INFO LED on output 13 blinks

#define INFO 13

void setup()
{
    Serial.begin(9600);
    Serial.println("Hello World!");
    
    pinMode(INFO, OUTPUT);
}


void loop()
{
    digitalWrite(INFO, 1);
    delay(500);
    digitalWrite(INFO, 0);
    delay(500);  
}
