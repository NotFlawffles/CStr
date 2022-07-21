#include "./../include/cstr.h"


strMatchPosition *cstrMatchNewStringPosition(int start, int end) {
    strMatchPosition *matchPosition = (strMatchPosition *) malloc(sizeof(strMatchPosition));
    matchPosition->start            = start;
    matchPosition->end              = end;
    return matchPosition;
}

strMatch *cstrMatchNew(int type) {
    strMatch *match         = (strMatch *) malloc(sizeof(strMatch));
    match->charsValue       = (char *) malloc(sizeof(char));
    match->charsPositions   = (int *) malloc(sizeof(long));
    match->charsSize        = 0;
    match->stringsValue     = (char **) malloc(sizeof(char));
    match->stringsPositions = (strMatchPosition **) malloc(sizeof(strMatchPosition));
    match->stringsSize      = 0;
    match->type             = type;
    return match;
}

strMatch *cstrMatchPutchar(strMatch *strmatch, char character, long position) {
    *(strmatch->charsPositions + strmatch->charsSize)   = position;
    *(strmatch->charsValue     + strmatch->charsSize++) = character;
    return strmatch;
}

strMatch *cstrMatchPutstring(strMatch *strmatch, char *string, strMatchPosition *position) {
    *(strmatch->stringsPositions + strmatch->stringsSize)   = position;
    *(strmatch->stringsValue     + strmatch->stringsSize++) = string;
    return strmatch;
}

str *cstrNew(void) {
    str *string    = (str *) malloc(sizeof(str));
    string->value  = (char *) malloc(sizeof(char));
    return string;
}

str *cstrFrom(char *string) {
    return cstrCopy(cstrNew(), string);
}

str *cstrCopy(str *string, char *cstring) {
    int clength = cstrGetLength(cstring);
    string->length = clength;
    char *_string = (char *) calloc(string->length, sizeof(char));
    for (int index = 0; index < clength; index++)
        *(_string + index) = *(cstring + index);
    string->value = _string;
    return string;
}

str *cstrPushChar(str *string, char character) {
    str *copy = cstrCopy(string, string->value);
    *(copy->value + string->length++) = character;
    return string;
}

str *cstrPushString(str *string, char *cstring) {
    str *copy = cstrCopy(string, string->value);
    int clength = 0;
    for (; *(cstring + clength); )
        cstrPushChar(copy, *(cstring + clength++));
    return string;
}

str *cstrReverse(str *string) {
    str *newValue = cstrNew();
    for (int index = string->length; index > -1; index--)
        cstrPushChar(newValue, *(string->value + index));
    return newValue;
}

str *cstrCharAt(str *string, int index) {
    if (index > string->length)
        return 0;
    if (index < 0)
        return cstrFrom(
            (char []) {
                *(string->value + (string->length + index)), 0
            });
    return cstrFrom(
        (char []) {
            *(string->value + index), 0
        });
}

strMatch *cstrMatchChar(str *string, char character) {
    strMatch *match = cstrMatchNew(MATCH_CHARACTER);
    for (int index = 0; index < string->length; index++)
        if (
                cstrCompare(cstrFrom((char []) {character, 0}),
                cstrCharAt(string, index)
        ))
            cstrMatchPutchar(match, character, index);
    return match;
}

strMatch *cstrMatchString(str *string, char *cstring) {
    strMatch *match = cstrMatchNew(MATCH_STRING);
    int index = 0;
    while (index < string->length) {
        int start, end;
        int temp = 0;
        if (
                cstrCompare(cstrCharAt(string, index),
                cstrFrom(cstring)
        )) {
            start = index;
            while (
                    *(cstring + temp) && *(string->value + index++) ==
                    *(cstring + temp++)
            );
            end   = index;
            cstrMatchPutstring(match, cstring, cstrMatchNewStringPosition(start, end));
        } else
            index++;
    }
    return match;
}

int cstrGetLength(char *string) {
    int clength    = 0;
    for (; *(string + clength); clength++);
    return clength;
}

int cstrAtoi(str *string) {
    int value = 0;
    int index = 0;
    bool negative = false;
    if (cstrCompare(
                cstrCharAt(string, index),
                cstrFrom("-")
        )) {
        negative = true;
        index++;
    }
    while (
        *(string->value + index) >= '0' &&
        *(string->value + index) <= '9'
    ) {
        value = value * 10 + (*(string->value + index) - '0');
        index++;
    }
    if (negative)
        value *= -1;
    return value;
}

bool cstrStartswith(str *string, char testchar) {
    return cstrCompare(
            cstrCharAt(string, 0),
            cstrFrom((char []) {testchar, 0})
        );
}

bool cstrEndswith(str *string, char testchar) {
    return cstrCompare(
            cstrCharAt(string, -1),
            cstrFrom((char []) {testchar, 0})
        );
}

bool cstrCompare(str *firstString, str *secondString) {
    if (!cstrLengthCompare(firstString, secondString))
        return false;
    for (int index = 0; index < firstString->length; index++)
        if (
                *(firstString->value + index) !=
                *(secondString->value + index)
        )
            return false;
    return true;
}

bool cstrLengthCompare(str *firstString, str *secondString) {
    return firstString->length == secondString->length;
}

bool cstrIsLower(str *string) {
    for (int index = 0; index < string->length; index++)
        if (
                *(string->value + index) >= 'A' &&
                *(string->value + index) <= 'Z'
        )
            return false;
    return true;
}

bool cstrIsHigher(str *string) {
    for (int index = 0; index < string->length; index++)
        if (
                *(string->value + index) >= 'a' &&
                *(string->value + index) <= 'z'
        )
            return false;
    return true;
}

bool cstrIsIdentifier(str *string) {
    for (int index = 0; index < string->length; index++)
        if (
                *(string->value + index) < 'A'   ||
                (*(string->value + index) > 'Z'  &&
                 *(string->value + index) < 'a') ||
                *(string->value + index) > 'z'
        ) {
            if (
                    *(string->value + index) >= '0' &&
                    *(string->value + index) <= '9'
            )
                if (index)
                    continue;
            if (*(string->value + index) == '_')
                continue;
            return false;
        }
    return true;
}

bool cstrIsSpace(str *string) {
    for (int index = 0; index < string->length; index++)
        if (
            !cstrCompare(cstrCharAt(string, index),
            cstrFrom(" ")
        ) &&
            !cstrCompare(cstrCharAt(string, index),
            cstrFrom("\n")
        ) &&
            !cstrCompare(cstrCharAt(string, index),
            cstrFrom("\t")
        ))
            return false;
    return true;
}

bool cstrIsBlank(str *string) {
    return !string->length;
}

bool cstrIsDigit(str *string) {
    for (int index = 0; index < string->length; index++)
        if (
                *(string->value + index) < '0' ||
                *(string->value + index) > '9'
        )
            return false;
    return true;
}
