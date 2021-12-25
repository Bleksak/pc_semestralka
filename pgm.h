/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief 
 * @version 1.0
 * @date 2021-10-16
 */

#include <stdint.h>
#include "error.h"

#ifndef PGM_H
#define PGM_H

ErrorCode pgm_load(const char* file, uint8_t** data, int* width, int* height);
ErrorCode pgm_write(const char* file, uint8_t* data, int width, int height);

#endif
