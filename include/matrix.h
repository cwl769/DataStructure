#ifndef _MATRIX_H_
#define _MATRIX_H_

#ifdef __cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdlib.h>

#define Matrix(type) struct {   \
    uint32_t h, w;  \
    type *addr;     \
}

#define matrix_create(matrix, type, height, width) do {     \
    (matrix)->h = (height);     \
    (matrix)->w = (width);      \
    (matrix)->addr = (type*)malloc((height)*(width)*sizeof(type));    \
} while (0)

#define matrix_delete(matrix) do {  \
    free((matrix)->addr); \
} while (0)

#define matrix_at(matrix, i, j) ( (matrix)->addr + (i)*(matrix)->w + (j) )

#define matrix_print(matrix, format) do {   \
    for(uint32_t i=0;i<(matrix)->h;++i) {        \
        for(uint32_t j=0;j<(matrix)->w;++j)      \
            printf(format" ", *matrix_at((matrix), i, j));   \
        printf("\n");                       \
    }   \
} while (0)

#define matrix_plus(result, a, b) do {  \
    for(uint32_t i=0;i<(result)->h;++i) {   \
        for(uint32_t j=0;j<(result)->w;++j){    \
            *matrix_at(result, i, j) = *matrix_at(a, i, j) + *matrix_at(b, i, j);   \
        }   \
    }   \
} while (0)

#define matrix_minus(result, a, b) do {  \
    for(uint32_t i=0;i<(result)->h;++i) {   \
        for(uint32_t j=0;j<(result)->w;++j){    \
            *matrix_at(result, i, j) = *matrix_at(a, i, j) - *matrix_at(b, i, j);   \
        }   \
    }   \
} while (0)

#define matrix_mul(result, a, b) do {           \
    for(uint32_t i=0;i<(a)->h;++i) {            \
        for(uint32_t j=0;j<(b)->w;++j) {        \
            *matrix_at(result, i, j) = 0;       \
            for(uint32_t k=0;k<(a)->w;++k) {    \
                *matrix_at(result, i, j) += (*matrix_at(a, i, k)) * (*matrix_at(b, k, j));  \
            }                                   \
        }                                       \
    }                                           \
} while (0)

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif