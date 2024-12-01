#include <stdio.h>
#include <stdarg.h>

#pragma once

int store_estimation(char *itemId, int value);

char* get_estimations(char *itemId);

void fwarnf(char *format, va_list args);