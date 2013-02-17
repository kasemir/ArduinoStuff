// Servo parameter persistence
// Copyright (c) 2011 Kay Kasemir.  All right reserved.

// EEPROM cell for position, 0...180 degrees
#define EEPROM_POS 0
// EEPROM cell for direction, -1, +1 mapped to 0, 1
#define EEPROM_DIR 1
 
class Persist
{
public:
    static void setPosition(int pos)
    {
        EEPROM.write(EEPROM_POS, pos);
    }

    static void setDirection(int dir)
    {
       EEPROM.write(EEPROM_DIR, dir > 0 ? 1 : 0);
    }
    
    static int getPosition()
    {
        return EEPROM.read(EEPROM_POS);
    }

    static int getDirection()
    {
        return (EEPROM.read(EEPROM_DIR) % 2) ? 1 : - 1;
    }
};

#undef EEPROM_POS
#undef EEPROM_DIR 1

