#include <stdarg.h>
#include <stdio.h>
#include "./headers/log.h"

void fwarnf(char *format, int argc, ...)
{
    va_list args;
    va_start(args, argc);
    switch(argc) {
        case 0:
            fprintf(stdout, "%s", format);
            break;
        case 1:
            fprintf(stdout, format, va_arg(args, char*));
            break;
        case 2:
            fprintf(stdout, format, va_arg(args, char*), va_arg(args, char*));
            break;
        case 3:
            fprintf(stdout, format, va_arg(args, char*), va_arg(args, char*), va_arg(args, char*));
            break;
        default:
            fprintf(stdout, "%s. %d arguments passed although those are limited to 3.", format, argc);
    }
    va_end(args);
}