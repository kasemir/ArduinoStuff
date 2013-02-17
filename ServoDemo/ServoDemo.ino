// Servo test
// Copyright (c) 2011 Kay Kasemir.  All right reserved.
//
// Adafruit board with servo on servo 1 or 2
// Also blinks LED (pin 13)
//
// 4298 bytes

#include <Servo.h>
#include <EEPROM.h>
#include "Persist.h"

// Servo pin assignments
#define ADA_SERVO1 10
#define ADA_SERVO2 9

// Move servo 0..180 deg but stopping at this limit before 0 resp. 180
#define POS_LIMIT 20
static Servo servo;
static int dir = 1;

void setup() 
{ 
    Serial.begin(9600);
    Serial.println("ServoStuff");
    pinMode(13, OUTPUT);
    digitalWrite(13, dir > 0);
    servo.attach(ADA_SERVO1);
    servo.write(POS_LIMIT);
    
    // Initialize servo position from EEPROM
    int pos = Persist::getPosition();
    if (pos >= POS_LIMIT  &&  pos <= (180-POS_LIMIT))
        servo.write(pos);
    dir = Persist::getDirection();
} 
 
void loop() 
{
    int pos = servo.read() + dir;
    if (pos < POS_LIMIT  ||  pos > (180-POS_LIMIT))
    {
       dir = -dir;
       digitalWrite(13, dir > 0);
       Persist::setDirection(dir);
    }
    servo.write(pos);
    Persist::setPosition(pos);
    delay(15);
} 
