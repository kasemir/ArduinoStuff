// Persistence-of-Vision support for Bits-of-Text
//
// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include <ctype.h>
#include "POVBits.h"

static byte char_a[] =
{
    //  **
    // *  *
    // *  *
    // *  *
    // ****
    // *  *
    // *  *
    // *  *
    B01111111,
    B10001000,
    B10001000,
    B01111111,
    0
};

static byte char_b[] =
{
    // ***
    // *  *
    // *  *
    // **
    // ***
    // *  *
    // *  *
    // ***
    B11111111,
    B10011001,
    B10001001,
    B01100110,
    0
};

static byte char_c[] =
{
    //  **
    // *  *
    // *
    // *
    // *
    // *
    // *  *
    //  **
    B01111110,
    B10000001,
    B10000001,
    B01000010,
    0
};

static byte char_d[] =
{
    // **
    // *  *
    // *  *
    // *  *
    // *  *
    // *  *
    // *  *
    // **
    B11111111,
    B10000001,
    B01111110,
    0
};

static byte char_e[] =
{
    // ***
    // *   
    // *   
    // *
    // ***
    // *
    // *
    // ***
    B11111111,
    B10001001,
    B10001001,
    0
};

static byte char_f[] =
{
    // ****
    // *   
    // *   
    // *
    // ***
    // *
    // *
    // *
    B11111111,
    B10001000,
    B10001000,
    B10000000,
    0
};

static byte char_g[] =
{
    0
};

static byte char_h[] =
{
    // *   *
    // *   *
    // *   *
    // *****
    // *****
    // *   *
    // *   *
    // *   *
    B11111111,
    B00011000,
    B00011000,
    B11111111,
    0
};

static byte char_i[] =
{
    //  *
    //  *
    //  *
    //  *
    //  *
    //  *
    //  *
    //  *
    B11111111,
    0
};

static byte char_j[] =
{
    0
};

static byte char_k[] =
{
    B11111,
    B00110,
    B01011,
    B10001,
    0
};

static byte char_l[] =
{
    //  *
    //  *
    //  *
    //  *
    //  *
    //  *
    //  *
    //  *****
    B11111111,
    B00000001,
    B00000001,
    B00000001,
    0
};

static byte char_m[] =
{
    0
};

static byte char_n[] =
{
    B11111,
    B11000,
    B01100,
    B00110,
    B00011,
    B11111,
    0
};

static byte char_o[] =
{
    0,
};

static byte char_p[] =
{
    // ***
    // *  *
    // *  *
    // *  *
    // ***
    // *
    // *
    // *
    B11111111,
    B10001000,
    B10001000,
    B01110000,
    0
};

static byte char_q[] =
{
    0
};

static byte char_r[] =
{
    0
};

static byte char_s[] =
{
    //  **
    // *  *
    // *
    // *   
    //  **
    //    *
    // *  *
    //  **
    B01110010,
    B10001001,
    B10001001,
    B01000110,
    0
};

static byte char_t[] =
{
    0
};

static byte char_u[] =
{
    0
};

static byte char_v[] =
{
    0
};

static byte char_w[] =
{
    0
};

static byte char_x[] =
{
    0
};

static byte char_y[] =
{
    B10000,
    B01000,
    B00111,
    B01000,
    B10000,
    0
};

static byte char_z[] =
{
    0
};

static byte char_dash[] =
{
    B0001000,
    B0001000,
    0
};

static byte char_smiley[] =
{
    //    *******
    //   *       *
    //  *  ** **  *
    // *           *
    // *  *     *  *
    //  *  *****  *
    //   *       *
    //    *******
    B00011000,
    B00100100,
    B01000010,
    B10001001,
    B10100101,
    B10100101,
    B10000101,
    B10100101,
    B10100101,
    B10001001,
    B01000010,
    B00100100,
    B00011000,
    0
};

static byte char_heart[] =
{
    //   ***     ***
    //  ****** ******
    //   ***********
    //    *********
    //     *******
    //      *****
    //       ***
    //        *
    B01000000,
    B11100000,
    B11110000,
    B01111100,
    B01111110,
    B00111111,
    B01111110,
    B01111100,
    B11110000,
    B11100000,
    B01000000,
    0
};

static byte char_epics_logo[] =
{
    //  *** ***
    //  *** ***
    //   *   *
    //   *************
    //           *   *
    //          *** ***
    //          *** ***
    //
    B11000000,
    B11110000,
    B11010000,
    B00010000,
    B11010000,
    B11110000,
    B11010000,
    B00010000,
    B00010110,
    B00011110,
    B00010110,
    B00010000,
    B00010110,
    B00011110,
    B00000110,
    0
};


static byte *chars[] =
{
    char_a,
    char_b,
    char_c,
    char_d,
    char_e,
    char_f,
    char_g,
    char_h,
    char_i,
    char_j,
    char_k,
    char_l,
    char_m,
    char_n,
    char_o,
    char_p,
    char_q,
    char_r,
    char_s,
    char_t,
    char_u,
    char_v,
    char_w,
    char_x,
    char_y,
    char_z,
    char_dash,
    char_smiley,
    char_heart,
    char_epics_logo,
};

POVBits::POVBits()
{
    setText("@");
    space = 0;
}

void POVBits::getBits(const char c)
{
    switch (c)
    {
    case ' ':
        space = 5;
        break;
    case '-':
        bits = chars['Z' - 'A' + 1];
        break;
    case '\001':
        bits = chars['Z' - 'A' + 2];
        break;
    case '\002':
        bits = chars['Z' - 'A' + 3];
        break;
    case '\003':
        bits = chars['Z' - 'A' + 4];
        break;
    default:
        bits = chars[toupper(c) - 'A'];
    }
}

void POVBits::setText(const char *text)
{
    this->text = text;
    len = strlen(text);
    char_idx = 0;
    getBits(text[char_idx]);
}

byte POVBits::getNextBits()
{
    byte result;
    byte end_of_char;
    // Currently at a 'space'?
    if (space >= 0)
    {
        --space;
        result = 0;
        end_of_char = space < 0;
    }
    else
    {   // Return bits from normal character
        result = *bits;
        ++bits;
        end_of_char = result == 0;
    }
    // End of character?
    if (end_of_char)
    {
        ++char_idx;
        if (char_idx >= len)
            char_idx = 0;
        getBits(text[char_idx]);
    }
    return result;
}

