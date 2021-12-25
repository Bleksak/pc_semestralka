/**
 * @file pgm.c
 * @author Jiri Velek (jvelek@students.zcu.cz)
 * @brief 
 * @version 1.0
 * @date 2021-10-16
 */


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pgm.h"

#define BUFFER_SIZE 512
#define PGM_SIGNATURE {'P', '5'}
#define MAX_VALUE 0xFF
#define MIN_VALUE 0x00

#define READLINE() fgets(buffer, sizeof(buffer), fp)

/**
 * @brief Nacte PGM soubor
 * @param file nazev souboru
 * @param data pixely obrazku
 * @param width sirka obrazku
 * @param height vyska obrazku
 */
ErrorCode pgm_load(const char* file, uint8_t** data, int* width, int* height) {
    size_t read_length, i;
    char buffer[BUFFER_SIZE];
    uint8_t c;
    ErrorCode code = CODE_OK;

    char signature[] = PGM_SIGNATURE;
    FILE* fp = fopen(file, "r");

    if(fp == NULL) {
        return CODE_BAD_FILE;
    }

    /* file ends too early */
    if(READLINE() == NULL) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    /* invalid (or no) signature */
    if(strncmp(signature, buffer, sizeof(signature)) != 0) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    /* file ends too early */
    if(READLINE() == NULL) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    /* file doesnt contain width or height */
    if(sscanf(buffer, "%d %d", width, height) != 2) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    read_length = (size_t) *width * (size_t) *height;

    /* width or height == 0 */
    if(read_length == 0) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    /* file ends too early */
    if(READLINE() == NULL) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    /* invalid max value */
    if(atoi(buffer) != MAX_VALUE) {
        fclose(fp);
        return CODE_INVALID_PGM;
    }

    *data = calloc(read_length, sizeof(uint8_t));

    if(*data == NULL) {
        fclose(fp);
        return CODE_OUT_OF_MEMORY;
    }

    for(i = 0; i < read_length; ++i) {
        /* file ends too early */
        if(feof(fp)) {
            free(data);
            fclose(fp);
            return CODE_INVALID_PGM;
        }

        c = (uint8_t) fgetc(fp);

        if(c != MIN_VALUE && c != MAX_VALUE) {
            free(data);
            fclose(fp);
            return CODE_INVALID_PGM;
        }

        (*data)[i] = c;
    }

    fclose(fp);
    return code;
}

/**
 * @brief zapise do souboru pixely ve formatu PGM
 * @param file nazev souboru
 * @param data pixely obrazku
 * @param width sirka obrazku
 * @param height vyska obrazku
 */
ErrorCode pgm_write(const char* file, uint8_t* data, int width, int height) {
    char signature[] = PGM_SIGNATURE;
    size_t write_size = (size_t) width * (size_t) height;
    FILE* fp = fopen(file, "w");

    if(fp == NULL) {
        return CODE_WRITE_ERROR;
    }

    fprintf(fp, "%.*s\n%d %d\n%d\n", (int)sizeof(signature), signature, width, height, MAX_VALUE);

    if(fwrite(data, sizeof(uint8_t), write_size, fp) != write_size) {
        fclose(fp);
        return CODE_WRITE_ERROR;
    }

    fclose(fp);
    return CODE_OK;
}
