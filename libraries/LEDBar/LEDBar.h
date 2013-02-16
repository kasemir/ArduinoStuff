// LED Bar
//
// Uses LEDs connected to digital outputs,
// by default to pins 3, 4, 5, 6, 7, 8, 9, 10,
// as a light bar.
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include <Arduino.h>

class LEDBar
{
    static byte led[];
    
    void init();
public:
    /** Initialize with default LED pins */
    LEDBar();

    /** Initialize
     *  @param led0... Must provide exactly 8 LED pins
     */
    LEDBar(int led0, ...);
    
    /** Silly Knight-Rider effect */
    void knightRider();
    
    /** Set LEDs in bar-graph fashion
     *  @param level 0..1023
     */
    void bar(int level);

    /** Set single LED
     *  @param level 0..1023
     */
    void level(int level);
};


