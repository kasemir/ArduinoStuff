// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include "Arduino.h"
// NOTE: Must also add this include to the main PDE
//       for compile search path to get set correctly
#include <SoftwareSerial.h>

/** Support for SparkFun Serial-enabled LCD
 *  
 *  One output pin is used to send serial data
 *  to the LCD.
 *
 *  Also supports scrolling across the whole display.
 *
 *  Hardcoded for 2 x 16 display size.
 */
class SerialLCD
{
    // Serial interface, only used for writing
    SoftwareSerial port;
    
    // Ring buffer
    char scroll_buf[32];
    
    //  Initial: start = size = 0.
    //  Indices of valid entries:
    //  [start], [start+1], ..., [start+size-1]
    //  with wrap-around at [capacity-1].
    int start, end, size;

    // Add one character to end of scroll buffer
    void scroll_char(char ch);

public:
    /** Initialize
     *  pin - output pin (typically: 2)
     */
    SerialLCD(int pin);
    
    /** Clear display */
    void clear();
    
    /** Set Backlight level 0...30 */
    void backlight(int level);
    
    /** Set position */
    void set(int position);
    
    /** Print text, appending at current position */
    void print(const char *text);

    /** Print number, appending at current position */
    void print(int number);
    
    /** Print text, scrolling display when full */
    void scroll(const char *text);

    /** Print number, scrolling display when full */
    void scroll(int number);
};

#define DEFAULT_LCD 2

