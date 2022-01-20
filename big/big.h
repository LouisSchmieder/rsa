//
// Created by louis on 20.01.22.
//

#ifndef RSA_BIG_H
#define RSA_BIG_H

#include <stddef.h>
#include <stdbool.h>

typedef unsigned char byte;

/**
 * @param data Holds the bytes of the integer
 * @param len Length of the data array
 * @param pos Integer positive or negative
 */
struct BigInt {
    byte * data;
    size_t len;
    bool pos;
};

typedef struct BigInt big;

big fromNumber(void * data, size_t length, bool positive);
big fromString(char * str, size_t length);

big addBig(big a, big b);
big subBig(big a, big b);

char * toString(big data);
void freeBig(big d);

#endif //RSA_BIG_H
