// Copyright 2011 by Kay Kasemir. All Rights Reserved.

#include "MorseDecoder.h"

/** Element of morse decoder tree
 *  dot and dash are used to traverse
 *  tree downward until all
 *  morse code elements are handled.
 *  Resulting node's text is then the decoded
 *  character or prosign.
 *
 *  Compared to a linar lookup, this requires
 *  usually 3..4 tree hops, not looping over 10+
 *  list elements.
 */
class CodeItem
{
public:
    CodeItem *dot, *dash;
    const char *text;
    
    CodeItem()
    {
        dot = dash = NULL;
        text = NULL;
    }
};

static CodeItem *decode_tree = NULL;

static void addToTree(CodeItem **tree, const char *code, const char *text)
{
    if (*tree == NULL)
       *tree = new CodeItem();
    CodeItem *item = *tree;
    switch (*code)
    {
    case '.':
        addToTree(&item->dot, ++code, text);
        break;
    case '-':
        addToTree(&item->dash, ++code, text);
        break;
    default:
        item->text = text;
    }
}

// Initialize decode tree
static void initDecodeTree()
{
    addToTree(&decode_tree, ".-",       "a");
    addToTree(&decode_tree, "-...",     "b");
    addToTree(&decode_tree, "-.-.",     "c");
    addToTree(&decode_tree, "-..",      "d");
    addToTree(&decode_tree, ".",        "e");
    addToTree(&decode_tree, "..-.",     "f");
    addToTree(&decode_tree, "--.",      "g");
    addToTree(&decode_tree, "....",     "h");
    addToTree(&decode_tree, "..",       "i");
    addToTree(&decode_tree, ".---",     "j");
    addToTree(&decode_tree, "-.-",      "k");
    addToTree(&decode_tree, ".-..",     "l");
    addToTree(&decode_tree, "--",       "m");
    addToTree(&decode_tree, "-.",       "n");
    addToTree(&decode_tree, "---",      "o");
    addToTree(&decode_tree, ".--.",     "p");
    addToTree(&decode_tree, "--.-",     "q");
    addToTree(&decode_tree, ".-.",      "r");
    addToTree(&decode_tree, "...",      "s");
    addToTree(&decode_tree, "-",        "t");
    addToTree(&decode_tree, "..-",      "u");
    addToTree(&decode_tree, "...-",     "v");
    addToTree(&decode_tree, ".--",      "w");
    addToTree(&decode_tree, "-..-",     "x");
    addToTree(&decode_tree, "-.--",     "y");
    addToTree(&decode_tree, "--..",     "z");
    addToTree(&decode_tree, "-----",    "0");
    addToTree(&decode_tree, ".----",    "1");
    addToTree(&decode_tree, "..---",    "2");
    addToTree(&decode_tree, "...--",    "3");
    addToTree(&decode_tree, "....-",    "4");
    addToTree(&decode_tree, ".....",    "5");
    addToTree(&decode_tree, "-....",    "6");
    addToTree(&decode_tree, "--...",    "7");
    addToTree(&decode_tree, "---..",    "8");
    addToTree(&decode_tree, "----.",    "9");
    addToTree(&decode_tree, "..--..",   "?");
    addToTree(&decode_tree, "-...-",    " = \n");
    addToTree(&decode_tree, "-.--.",    "<KN>");
    addToTree(&decode_tree, ".-...",    "<AS>");
    addToTree(&decode_tree, "........", "<ERR>\n");
    addToTree(&decode_tree, "...-.-",   "<SK>");
    addToTree(&decode_tree, ".-.-.-",   ". ");
    addToTree(&decode_tree, "--..--",   ", ");
}

MorseDecoder::MorseDecoder()
{
    if (decode_tree == NULL)
        initDecodeTree();

    clear();
}

void MorseDecoder::clear()
{
    buf_idx = 0;
    buf[buf_idx] = '\0';
}

void MorseDecoder::add(const char morse)
{
    if (buf_idx >= sizeof(buf))
        return;
    buf[buf_idx++] = morse;
    buf[buf_idx] = '\0';
}

const char *MorseDecoder::decode()
{
    const char *text = decode(buf);
    clear();
    return text;
}

const char *MorseDecoder::decode(const char *morse)
{
    const char *code = morse;
    CodeItem *item = decode_tree;
    while (*code && item)
    {
        switch (*code)
        {
        case '.':
            item = item->dot;
            break;
        case '-':
            item = item->dash;
            break;
        }
        ++code;
    }
    if (item != NULL)
        return item->text;

    // Unknown
    sprintf(error_msg, " %s ", morse);
    return error_msg;
}

