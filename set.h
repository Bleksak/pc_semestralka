/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief 
 * @version 1.0
 * @date 2021-10-16
 */

#include <stdint.h>

#ifndef SET_H
#define SET_H

typedef struct DisjointSet {
    int next;
    uint8_t value;
} DisjointSet;

/**
 * @brief provede operaci find
 * @param arr pole vrcholu
 * @param x index pocatecniho vrcholu
 */
DisjointSet* find(DisjointSet* arr, int x);

/**
 * @brief provede operaci union
 * @param arr pole vrcholu
 * @param a prvni vrchol
 * @param b druhy vrchol
 * @param value pokud vrchol nema prirazenou hodnotu, pak ji priradi
 */
void onion(DisjointSet* arr, int a, int b, uint8_t value);

#endif
