// Persistence-of-Vision support for Bits-of-Text
//
// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include "Arduino.h"

/** Support for turning text into bits
 */
class POVBits
{
    const char *text;
    int len;
    int char_idx;
    byte *bits;
    int space;

    void getBits(const char c);
    
public:
    // Initialize
    POVBits();
    
    // Set the text.
    // Most uppercase chars are supported,
    // also:
    // ' ' -> Space
    // '\001' -> Smiley
    // '\002' -> Heart
    // '\003' -> EPICS Logo
    void setText(const char *text);
    
    // Get bits for the next char
    byte getNextBits();
};

#define  SMILEY  "\001"
#define  HEART   "\002"
#define  EPICS   "\003"


