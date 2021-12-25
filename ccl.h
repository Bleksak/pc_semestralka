/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief Implementace algoritmu CCL(Connected Component Labeling)
 * @version 1.0
 * @date 2021-10-16
 */

#include "error.h"
#include <stdint.h>

#ifndef LABELING_H
#define LABELING_H

/**
 * @brief algoritmus connected-component labeling
 * @param data pixely obrazku
 * @param w sirka obrazku
 * @param h vyska obrazku
 */
ErrorCode labeling(uint8_t* data, int w, int h);

#endif
