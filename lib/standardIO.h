#include "stdarg.h"

#ifndef STANDARDIO_H
#define STANDARDIO_H

typedef enum toASCII_t{
    toASCII_dec = 10,
    toASCII_hex = 16,
    toASCII_bin = 2,
} toASCII_t;

uint32_t printingString(const char* s);
uint32_t gettingString(void);
uint32_t printingFormat(const char* format, ...);
uint32_t printFormatString(char* buffer, const char* format, va_list arg);
uint32_t toASCII(char* buffer, uint32_t val, toASCII_t base);

#endif // STANDARDIO_H