/*
 FadeStuff
 
 Red, Green, Blue LEDs on outputs 9, 10, 11
 
 */
 
// --------------------------------------
/* LED.h */
 
#ifndef _LED_H_
#define _LED_H_

// #include "Arduino.h"

/* Support for one LED
 * Can fade in/out, remembers current 'brightness'
 * and allows configuration of 'full' brightness
 * to calibrate LEDs of different intensities.
 */
class LED
{
private:
    static int fade;
    static int sleep;
    int pin;
    int full;
    int brightness;

public:
    /** Initialize
     *  pin - output pin that supports PWM (9, 10, ...)
     *  full - Output value for full intensity (0..255)
     */
    LED(int pin, int full);

    static void setFade(int fade);    

    /** brightness - Output value 0..255 */
    void set(int brightness);

    /** Turn LED to full intensity */
    void on();

    /** Turn LED off */
    void off();

    void fade_on();

    void fade_off();
};

#endif

// --------------------------------------
/* LED.cpp */
 
// #include "LED.h"

int LED::fade = 10;
int LED::sleep = 10;

LED::LED(int pin, int full)
{
    this->pin = pin;
    this->full = full;
    pinMode(pin, OUTPUT);
    off();
}

void LED::setFade(int fade)
{
    LED::fade = fade;
}    

void LED::set(int brightness)
{
    if (brightness > full)
        this->brightness = full;
    else if (brightness < 0)
        this->brightness = 0;
    else
        this->brightness = brightness;
    analogWrite(pin, brightness);
}
    
void LED::on()
{
    set(full);
} 

void LED::off()
{
    set(0);
}

void LED::fade_on()
{
    const int actual_fade = fade * full / 255;
    while (brightness < full)
    {
        set(brightness + actual_fade);
        delay(sleep);
    }
    on();
}

void LED::fade_off()
{
    const int actual_fade = fade * full / 255;
    while (brightness > 0)
    {
        set(brightness - actual_fade);
        delay(sleep);
    }
    off();
}

// --------------------------------------

static LED red(9, 255);
static LED green(10, 155);
static LED blue(11, 155);

void setup()
{
    Serial.begin(9600);
    Serial.println("LEDColors");
} 

void loop()
{
    // "White"
    red.on();
    green.on();
    blue.on();
    delay(1000);

    // "Purple"
    red.on();
    green.off();
    blue.on();
    delay(1000);

    // "Yellow"
    red.on();
    green.on();
    blue.off();
    delay(1000);

    // ?
    red.off();
    green.on();
    blue.on();
    delay(1000);
    
    // Cycle though LEDs, getting faster
    green.off();
    blue.off();
    for (int i=0; i<10; ++i)
    {
        for (int fade = 10; fade < 60; fade += 5)
        {
            LED::setFade(fade);
            red.fade_on();
            red.fade_off();
    
            green.fade_on();
            green.fade_off();
    
            blue.fade_on();
            blue.fade_off();
            
            red.off();
            green.off();
            blue.off();
        }
    }
}
