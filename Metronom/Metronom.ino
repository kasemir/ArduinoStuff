/*
  Metronom
  
  Based on 'Melody' example by Tom Igoe 
  http://arduino.cc/en/Tutorial/Tone

  Circuit:
  * 8-ohm speaker on digital pin 8
  * Pot on analog input 0 (gnd, 5V, center on input)
 
 */
#include "pitches.h"

#define SPEAKER 8
#define SPEED A0

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3,0, NOTE_B3, NOTE_C4};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4,4,4,4,4 };

void setup()
{
    // iterate over the notes of the melody:
    for (int thisNote = 0; thisNote < 8; thisNote++)
    {
        // to calculate the note duration, take one second 
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/noteDurations[thisNote];
        tone(SPEAKER, melody[thisNote],noteDuration);
        
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pauseBetweenNotes = noteDuration * 1.30;
        delay(pauseBetweenNotes);
        // stop the tone playing:
        noTone(SPEAKER);
    }
  
    int speed = 300;
    int i=0;
    while (true)
    {
        if (i == 0)
        {
            tone(SPEAKER, 300, 10);
            speed = analogRead(SPEED);
        }
        else
            tone(SPEAKER, 100, 10);
        delay(200);
        noTone(SPEAKER);
        delay(speed);
        i = (i + 1) % 4;
    }
}

void loop()
{
}
