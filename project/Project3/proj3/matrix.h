//matrix.h
#ifndef _MATRIX_H
#define _MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define START start = clock()
#define END(message) end = clock();\
        printf("%s cost %.8lf ms.\n", message, (1000.0 * (double)(end-start))/CLOCKS_PER_SEC)

extern clock_t start, end;

typedef struct matrix_1 {
    size_t col;
    size_t row;
    float *val;
} mat, *matp;

typedef struct matrix_2 {
    size_t col;
    size_t row;
    float **val;
} mat_2, *matp_2;


void mat_del(matp);

void mat_del_2(matp_2);

void mat_copy(matp, const matp);

void mat_copy_to2(matp_2, const matp);

void mat_match_check(matp, const matp, const matp);

void mat_match_check_2(matp_2, const matp_2, const matp_2);

void mat_compare(const matp, const matp_2);

#endif //_MATRIX_H
