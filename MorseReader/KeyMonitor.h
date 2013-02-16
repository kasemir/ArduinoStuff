// Monitor a (morse) key
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include<Arduino.h>

class KeyMonitor
{
    enum
    {
        idle,        // Waiting, nothing happened for a while
        key_down,    // Key is down
        key_up,      // Key back up
        end_of_char, // Key up long enough to indicate end-of-char
        end_of_word  // .... for end-of-word
    } state;
    
    // Time in millis when key was put down
    unsigned long start_keydown;

    // Time in millis when key was last released
    unsigned long end_keydown;

    // Average length of dits and dahs
    int dit_avg, dah_avg;
    
    // Threshold in millis to consider a key-down period as a 'dah'.
    // Shorter key-downs are read as a 'dit'
    int dah_threshold;
    
public:
    /** Initialize */
    KeyMonitor();
    
    /** Handle current key state
     *  @param is_key_down - is key currently down?
     *  @result IDLE, DIT, DAH, END_OF_CHAR, END_OF_WORD
     */
    char handleKey(const boolean is_key_down);
};

/** Nothing new to report */
#define IDLE '\0'
/** Received a 'dit' */
#define DIT '.'
/** Received a 'dah' */
#define DAH '-'
/** Received pause at end of char. Should decode the char */
#define END_OF_CHAR ' '
/** Received pause at end of word */
#define END_OF_WORD '\n'

