#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ESTIMATION[100] = {'\0'};

int store_estimation(char *itemId, int value) 
{
    sprintf(ESTIMATION, "%s%d\n", ESTIMATION, value);
    return 0;
}

char* get_estimations(char *itemId) 
{
    char *tmp = malloc(strlen(ESTIMATION)*sizeof(char));
    strcpy(tmp, ESTIMATION);
    memset(ESTIMATION, '\0', strlen(ESTIMATION));
    return tmp;
}