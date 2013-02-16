// LM34 Temperature Measurement
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include<Arduino.h>

class LM34
{
private:
    int pin;

    /** @return Temperature in 10*Fahrenheit, e.g. 653 for 65.3F */
    int degTenF();

public:
    /** Initialize
     *  @param pin Analog input pin for LM34 signal
     */
    LM34(int pin);
    
    /** @return Temperature in Fahrenheit */
    float degF()
    {
        return 0.1 * degTenF();
    }

    /** @return Temperature in Celsius */
    float degC()
    {
        return (degF()-32)*5/9;
    }
};

#define DEFAULT_LM34 0

