/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief Zpracovani chybovych kodu
 * @version 1.0
 * @date 2021-10-16
 */

#include "error.h"
#include <stdio.h>

static const char* error_messages[] = {
    "Out of memory!",
    "Bad file!",
    "Invalid input file!",
    "Write error!",
    "Null pointer error!",
};

void print_error(ErrorCode code) {
    if(code != CODE_OK) {
        printf("ERROR#%d: %s\n", code, error_messages[code - 1]);
    }
}
