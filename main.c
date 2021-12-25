/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief 
 * @version 1.0
 * @date 2021-10-16
 */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ccl.h"
#include "pgm.h"

#define PGM_EXT ".pgm"

static char* get_input_name(const char* in) {
    const char* s = strrchr(in, '.');
    size_t len = strlen(in);
    char* tmp;

    if(s && strcmp(s, PGM_EXT) == 0) {
        tmp = calloc(len + 1, sizeof(char));
        strcpy(tmp, in);
    } else {
        tmp = calloc(len + sizeof(PGM_EXT) + 1, sizeof(char));
        strcpy(tmp, in);
        strcpy(tmp + len, PGM_EXT);
    }

    return tmp;
}


int main(int argc, const char** argv) {

    char* input;
    const char* output;

    uint8_t* data;
    int width;
    int height;

    ErrorCode code;

    if(argc < 3) {
        return EXIT_FAILURE;
    }

    input = get_input_name(argv[1]);
    output = argv[2];


    code = pgm_load(input, &data, &width, &height);
    if(code) {
        free(input);
        print_error(code);
        return code;
    }

    code = labeling(data, width, height);

    if(code) {
        free(data);
        free(input);
        print_error(code);
        return code;
    }

    code = pgm_write(output, data, width, height);
    free(data);
    free(input);

    if(code) {
        print_error(code);
    }

    return code;
}
