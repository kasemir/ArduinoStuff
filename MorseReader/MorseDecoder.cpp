// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include "MorseDecoder.h"

typedef struct
{
    const char *code; // "-.-."
    const char *text; // "c"
} MorseCode;

static MorseCode codes[] =
{
    { ".-",       "a" },
    { "-...",     "b" },
    { "-.-.",     "c" },
    { "-..",      "d" },
    { ".",        "e" },
    { "..-.",     "f" },
    { "--.",      "g" },
    { "....",     "h" },
    { "..",       "i" },
    { ".---",     "j" },
    { "-.-",      "k" },
    { ".-..",     "l" },
    { "--",       "m" },
    { "-.",       "n" },
    { "---",      "o" },
    { ".--.",     "p" },
    { "--.-",     "q" },
    { ".-.",      "r" },
    { "...",      "s" },
    { "-",        "t" },
    { "..-",      "u" },
    { "...-",     "v" },
    { ".--",      "w" },
    { "-..-",     "x" },
    { "-.--",     "y" },
    { "--..",     "z" },
    { "-----",    "0" },
    { ".----",    "1" },
    { "..---",    "2" },
    { "...--",    "3" },
    { "....-",    "4" },
    { ".....",    "5" },
    { "-....",    "6" },
    { "--...",    "7" },
    { "---..",    "8" },
    { "----.",    "9" },
    { "..--..",   "?" },
    { "-...-",    " = \n" },
    { "-.--.",    "<KN>" },
    { ".-...",    "<AS>" },
    { "........", "<ERR>\n" },
    { "...-.-",   "<SK>" },
    { ".-.-.-",   ". " },
    { "--..--",   ", " },
};

char MorseDecoder::error_msg[53];

/** Initialize */
MorseDecoder::MorseDecoder()
{
    buf_idx = 0;
    buf[buf_idx] = '\0';
 }
 
/** Add a morse bit to the decoder buffer
 *  morse: '-' or '.'
 */
void MorseDecoder::add(const char morse)
{
    if (buf_idx >= sizeof(buf))
        return;
    buf[buf_idx++] = morse;
    buf[buf_idx] = '\0';
}

/** Decode accumulated buffer content
 *  Returns: Text or ""
 */
const char *MorseDecoder::decode()
{
    const char *text = decode(buf);
    buf_idx = 0;
    buf[buf_idx] = '\0';
    return text;
}

const char *MorseDecoder::decode(const char *morse)
{
    for (int i=0;  i<(sizeof(codes)/sizeof(codes[0])); ++i)
        if (! strcmp(morse, codes[i].code))
            return codes[i].text;
    // Unknown
    error_msg[0] = ' ';
    strcpy(&error_msg[1], morse);
    strcat(error_msg, "? ");
    return error_msg;
}

