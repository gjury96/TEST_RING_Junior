#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include "aes.h"

uint8_t datae[] = { };
uint8_t datad[] = { };
uint8_t out[] = { };
uint8_t str[100];
uint8_t key[32];
uint8_t size;
FILE *f1, *f2, *f3;
uint32_t crc32;           

  