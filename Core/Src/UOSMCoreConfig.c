//
// Created by Jeremy Cote on 2023-08-29.
//

#include "UOSMCoreConfig.h"

#ifndef STM32

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>

static char messageBuf[MAX_SERIAL_PRINT_LENGTH];

void ExternalSerialPrint(const char * message, ...) {
    va_list args;
    va_start(args, message);
    printf(message, args);
    va_end(args);
}
void ExternalSerialPrintln(const char * message, ...) {
    va_list args;
    va_start(args, message);
    uint16_t len = vsprintf(messageBuf, message, args);
    messageBuf[len] = '\n';
    messageBuf[len+1] = '\r';
    printf(messageBuf, args);
    va_end(args);
}

#endif