#include <stdint.h>

/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief
 * @version 1.0
 * @date 2021-10-16
 */

#include <stdio.h>
#include <stdlib.h>

#include "ccl.h"
#include "error.h"
#include "set.h"

#define BACKGROUND 0
#define ARR_SIZE(x) (sizeof(x) / sizeof(x[0]))

static int union_neighbors(DisjointSet* arr, uint8_t* data, int w, int h, int x,
                           int y, uint8_t next_label) {
    int dx[] = {0, 1, 1};
    int dy[] = {1, 0, 1};

    size_t i;
    int cx, cy;
    int count = 0;

    for (i = 0; i < ARR_SIZE(dx); ++i) {
        cx = x + dx[i];
        cy = y + dy[i];

        if (cx >= w || cx < 0 || cy >= h || cy < 0) {
            continue;
        }

        if (data[cy * w + cx] != BACKGROUND &&
            data[cy * w + cx] == data[y * w + x]) {
            onion(arr, y * w + x, cy * w + cx, next_label);
            count = 1;
        }
    }

    return count;
}

static void relabel(uint8_t* data, int x, int y, int w, uint8_t label,
                    uint8_t label_count) {
    uint8_t max = UCHAR_MAX;
    uint8_t min = 1;

    data[y * w + x] = label * (max - min) / label_count;
}

ErrorCode labeling(uint8_t* data, int w, int h) {
    int x, y, i;
    uint8_t next_label = 1;
    DisjointSet* component;

    DisjointSet* arr = calloc((size_t)(w * h), sizeof(DisjointSet));

    if (arr == NULL) {
        return CODE_OUT_OF_MEMORY;
    }

    for (i = 0; i < w * h; ++i) {
        arr[i].next = i;
    }

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            if (data[y * w + x] == BACKGROUND) {
                continue;
            }

            if(!union_neighbors(arr, data, w, h, x, y, next_label)) {
                next_label++;
            }
        }
    }

    for (y = 0; y < h; ++y) {
        for (x = 0; x < w; ++x) {
            if (data[y * w + x] == BACKGROUND) {
                continue;
            }

            component = find(arr, y * w + x);

            relabel(data, x, y, w, component->value, next_label - 1);
        }
    }

    free(arr);
    return CODE_OK;
}
