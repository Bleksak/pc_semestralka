/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief Implementace algoritmu union find
 * @version 1.0
 * @date 2021-10-16
 */

#include "set.h"

/**
 * @brief provede operaci find
 * @param arr pole vrcholu
 * @param x index pocatecniho vrcholu
 */
DisjointSet* find(DisjointSet* arr, int x) {
    int next;
    while (x != arr[x].next) {
        next = arr[x].next;
        x = arr[x].next = arr[next].next;
    }

    return &arr[x];
}

/**
 * @brief provede operaci union
 * @param arr pole vrcholu
 * @param a prvni vrchol
 * @param b druhy vrchol
 * @param value pokud vrchol nema prirazenou hodnotu, pak ji priradi
 */
void onion(DisjointSet* arr, int a, int b, uint8_t value) {
    while (arr[a].next != a) {
        arr[a].value = arr[arr[a].next].value;
        a = arr[a].next;
    }
    while (arr[b].next != b) {
        b = arr[b].next;
        arr[b].value = arr[a].value;
    }

    if(arr[a].value == 0) {
        arr[a].value = value;
    }

    arr[b].next = a;
    arr[b].value = arr[a].value;
}
