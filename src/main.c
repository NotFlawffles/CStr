#include "./../include/cstr.h"


int main(void) {
    str *string = cstrFrom("420");
    printf("%d\n", cstrIsDigit(string));
    return 0;
}
