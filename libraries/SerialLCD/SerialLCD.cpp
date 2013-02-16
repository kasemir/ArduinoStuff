// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include "SerialLCD.h"

SerialLCD::SerialLCD(int pin)
  : port(0, pin), start(0), end(0), size(0)
{
    pinMode(pin, OUTPUT);
    port.begin(9600);
}

void SerialLCD::clear()
{
   port.write(0xFE);
   port.write(0x01);
   start = 0;
   end = 0;
   size = 0;
}

void SerialLCD::backlight(int level)
{
    if (level < 0)
        level = 0;
    if (level >= 30)
        level = 29;
   port.write(0x7C);
   port.write(128+level);
}

// position = line 1: 0-15, line 2: 16-31, 31+ defaults back to 0
void SerialLCD::set(int position)
{
   if (position > 31)
       position = 0;
    port.write(0xFE);
    if (position<16)
        port.write(position+128);
    else
        port.write(position+48+128);
}

void SerialLCD::print(const char *text)
{
    while (*text != '\0')
        port.write(*(text++));
}

void SerialLCD::print(int number)
{
    char buf[20];
    print(itoa(number, buf, 10));
}

void SerialLCD::scroll_char(char ch)
{
    if (size >= sizeof(scroll_buf))
    {   // Overwrite start of buffer
        ++start;
        if (start >= sizeof(scroll_buf))
            start = 0;
    }
    else // Still filling buffer
        ++size;
    int i = (start + size - 1) % sizeof(scroll_buf);
    scroll_buf[i] = ch;
}

void SerialLCD::scroll(const char *text)
{
    // Add text to scroll buffer
    size_t len = strlen(text);
    for (int i=0; i<len; ++i)
        scroll_char(text[i]);
        
    // Display scroll buffer content
    int i = start;
    for (int c=0; c<size; ++c)
    {
        if (c == 0)
            set(0);
        else if (c == 16)
            set(16);
        port.print(scroll_buf[i]);
        ++i;
        if (i >= sizeof(scroll_buf))
            i = 0;
    }
}

void SerialLCD::scroll(int number)
{
    char buf[20];
    scroll(itoa(number, buf, 10));
}


