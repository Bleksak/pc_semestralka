/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief 
 * @version 1.0
 * @date 2021-10-16
 */

#ifndef ERROR_H
#define ERROR_H

typedef enum ErrorCode {
    CODE_OK = 0,
    CODE_OUT_OF_MEMORY,
    CODE_BAD_FILE,
    CODE_INVALID_PGM,
    CODE_WRITE_ERROR,
    CODE_NULL_PTR
} ErrorCode;

/**
 * @brief vypise chybovou hlasku k predanemu kodu
 * @param code chybovy kod
 */
void print_error(ErrorCode code);

#endif
