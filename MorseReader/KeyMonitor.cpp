// Monitor a (morse) key
//
// Copyright 2013 by Kay Kasemir. All Rights Reserved.

#include "KeyMonitor.h"

#undef DEBUG_KEY
#define ADAPT

#define MIN_DIT 20
#define MAX_DAH 500

/** Initialize */
KeyMonitor::KeyMonitor()
   : state(idle), dit_avg(50), dah_avg(200), dah_threshold(100)
{
}

/** Handle current key state
 *  is_key_down - is key currently down?
 */
char KeyMonitor::handleKey(const boolean is_key_down)
{
    if (is_key_down)
    {
        if (state != key_down)
        {   // Remember when keyed 'down'
            start_keydown = millis();            
            state = key_down;
        }
        return IDLE;
    }
    
    // Key is right now 'up'
    if (state == key_down)
    {   // Key was just released; determine how long key was 'down'
        end_keydown = millis();
        // Times in millisec will roll over after about 50 days,
        // but that is OK:
        // For example, the start may be 4294967291 (== FFFFFFFB == -5)
        // and the end may be 5, time would still come out as 10
        // because of unsigned long computation
        const unsigned long time = end_keydown - start_keydown;

        // Key is up
        state = key_up;

        // If key was only down for very short time,
        // assume it's a bounce, so wait until it stays
        // up longer
        if (time < dit_avg/3)
            return IDLE;

#ifdef DEBUG_KEY
        Serial.print("keyed ");
        Serial.print(time);
        Serial.println(" ms");
#endif
        if (time > dah_threshold)
        {   // It's a 'dah'
            // Adjust 10% of the 'dah' average with this reading
            dah_avg = (dah_avg*9 + time)/10;
            if (dah_avg > MAX_DAH)
                dah_avg = MAX_DAH;
            return DAH;
        }
        else
        {   // It's a 'dit'
            // Adjust 10% of the 'dit' average with this reading
            dit_avg = (dit_avg*9 + time)/10;
            if (dit_avg < MIN_DIT)
                dit_avg = MIN_DIT;
            return DIT;
        }
    }
    else
    {   // Key is and has been 'up' for some time.
        // Determine how long since last dit/dah
        const unsigned long time = millis() - end_keydown;
        if (state == key_up  &&  time > dah_avg)
        {   // Paused for one 'dah' -> Reached end of character
            state = end_of_char;
            return END_OF_CHAR;
        }
        else if (state == end_of_char  &&  time > 3*dah_avg)
        {   // Paused for longer 'dah' -> Reached end of word
            state = end_of_word;
#ifdef ADAPT
            // Update dah_threshold
            // The average dit length is weighted 3 times higher
            // to move the threshold towards shorter times
            dah_threshold = (dit_avg*3 + dah_avg)/4;
#endif
            return END_OF_WORD;
        }
        else if (state == end_of_word  &&  time > 5000)
        {   // Long pause: Show some info, return to idle
            state = idle;
            Serial.print("\nAvg. dit : ");
            Serial.print(dit_avg);
            Serial.println("ms");
            Serial.print("Avg. dah : ");
            Serial.print(dah_avg);
            Serial.println("ms");
            Serial.print("Threshold: ");
            Serial.print(dah_threshold);
            Serial.println("ms");

            // Compute WPM
            // PARIS = .--. .- .-. .. ...
           const unsigned long paris = dit_avg * 10 + // dits
                                       dah_avg *  4 + // dahs
                                       dah_avg *  7;  // spaces
           const unsigned long wpm = 60L*1000L / paris;
           Serial.print("WPM      : ");
           Serial.println(wpm);
        }
        return IDLE;
    }
}

