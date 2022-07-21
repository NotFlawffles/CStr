#ifndef CSTR_H
#define CSTR_H
#include <malloc.h>
#include <stdbool.h>


typedef struct {
   int start;
   int end;
} strMatchPosition;

strMatchPosition *cstrMatchNewStringPosition(int start, int end);

typedef struct {
    enum {
        MATCH_CHARACTER,
        MATCH_STRING,
    } type;
    char   *charsValue;
    int    *charsPositions;
    int     charsSize;
    char  **stringsValue;
    strMatchPosition **stringsPositions;
    int     stringsSize;
} strMatch;

strMatch *cstrMatchNew       (int type);
strMatch *cstrMatchPutchar   (strMatch *strmatch, char character, long position);
strMatch *cstrMatchPutstring (strMatch *strmatch, char *string, strMatchPosition *position);

typedef struct {
    int length;
    char *value;
} str;

str       *cstrNew           (void);
str       *cstrFrom          (char *string);
str       *cstrCopy          (str *string, char *cstring);
str       *cstrPushChar      (str *string, char character);
str       *cstrPushString    (str *string, char *cstring);
str       *cstrReverse       (str *string);
str       *cstrCharAt        (str *string, int index);
strMatch  *cstrMatchChar     (str *string, char character);
strMatch  *cstrMatchString   (str *string, char *cstring);
int        cstrGetLength     (char *string);
int        cstrAtoi          (str *string);
bool       cstrStartswith    (str *string, char testchar);
bool       cstrEndswith      (str *string, char testchar);
bool       cstrCompare       (str *firstString, str *secondString);
bool       cstrLengthCompare (str *firstString, str *secondString);
bool       cstrIsLower       (str *string);
bool       cstrIsHigher      (str *string);
bool       cstrIsIdentifier  (str *string);
bool       cstrIsSpace       (str *string);
bool       cstrIsBlank       (str *string);
bool       cstrIsDigit       (str *string);

#endif // CSTR_H
