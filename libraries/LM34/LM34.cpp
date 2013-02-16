// LM34 Temperature Measurement
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.


#include "LM34.h"

LM34::LM34(int pin)
    : pin(pin)
{
}

int LM34::degTenF()
{
    int adc = analogRead(pin);    
    int millivolt = (adc * 5000L)/1024;
    return millivolt;
}


