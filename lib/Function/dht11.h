#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "test.h"
#define MAXTIMINGS  85
#define DHTPIN    7

typedef struct {
    uint8_t humidity_int;
    uint8_t humidity_dec;
    uint8_t temperature_int;
    uint8_t temperature_dec;
    uint8_t data[5];
} DHTData;


int read_dht_data(DHTData *dht_data);