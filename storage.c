#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char *ESTIMATION;

int store_estimation(char *itemId, int value) 
{
    if (ESTIMATION == NULL) {
        ESTIMATION = malloc(sizeof(char));
    }
    char *tmp = malloc(strlen(ESTIMATION)*sizeof(char)+ceil(log10(value))*sizeof(char)+sizeof('\n'));
    sprintf(tmp, "%s%d\n", ESTIMATION, value);
    free(ESTIMATION);
    ESTIMATION = tmp;
    return 0;
}

char* get_estimations(char *itemId) 
{
    char *tmp = malloc(strlen(ESTIMATION)*sizeof(char));
    strcpy(tmp, ESTIMATION);
    memset(ESTIMATION, '\0', strlen(ESTIMATION));
    return tmp;
}