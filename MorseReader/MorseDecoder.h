// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include "Arduino.h"
#include "BenchTimer.h"

/** Decode ".-.-" into text */
class MorseDecoder
{
    // Buffer for accumulating dits and dahs
    char buf[50];

    // Buffer index, 0 for empty buffer
    int buf_idx;
    
    // Buffer for error
    char error_msg[53];
    
    // Clear buffer
    void clear();

public:
    /** Initialize */
    MorseDecoder();
         
    /** Add a morse bit to the decoder buffer
     *  morse: '-' or '.'
     */
    void add(const char morse);
    
    /** Decode accumulated buffer content
     *  Returns: Text or ""
     */
    const char *decode();

    /** Decode
     *  morse: "-.-."
     *  Returns: Text "c" or ""
     */
    const char *decode(const char *morse);
};

