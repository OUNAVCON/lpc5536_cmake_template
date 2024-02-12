#ifndef _DATA_TYPE_H_
#define _DATA_TYPE_H_

#inclde "stdint.h"

typedef struct {
    uint8_t writeToNvm : 1;
    uint8_t unused1 : 1;
    uint8_t unused2 : 1;
    uint8_t unused3 : 1;
    uint8_t unused4 : 1;
    uint8_t unused5 : 1;
    uint8_t unused6 : 1;
    uint8_t unused7 : 1;
}status_bits_t;

typedef enum status_t{
    uint8_t value;
    status_bits_t bits;
}

typedef enum float_t{
    uint8_t uint8Array[4];
    uint16_t uint16Array[2];
    float floatValue;
};


typedef struct {
    float_t data;
    uint16_t nvmAddress;
    status_t status;
}dataType_t;


#endif