#include <stdarg.h>
#include <stdio.h>
#include "./headers/log.h"

void fwarnf(char *format, va_list args)
{
    fprintf(stdout, format, args);
}