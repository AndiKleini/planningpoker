#include <stdarg.h>
#include <stdio.h>
#include <log.h>

void fwarnf(char *format, va_list args)
{
    fprintf(stdout, format, args);
}