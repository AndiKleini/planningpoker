#include <stdlib.h>
#include <stdio.h>
#include "./headers/handler.h"
#include <string.h>
#include <math.h>

int ESTIMATED;

struct response * process_request(char* buffer)
{
    char *cmd = strtok(buffer, "\n");
    if (strcmp(cmd, "ESTIMATE") == 0) {
        ESTIMATED = atoi(strtok(NULL, "\n"));
        ESTIMATED = atoi(strtok(NULL, "\n"));
        struct response *resp = (struct response *)malloc(sizeof(struct response));
        resp->msg = "OK";
        resp->size = 2;
        return resp;
    } else {
        struct response *resp = (struct response *)malloc(sizeof(struct response));
        resp->msg=malloc((int)ceil(log10(ESTIMATED)));
        sprintf(resp->msg, "%d", ESTIMATED);
        resp->size = strlen(resp->msg);
        return resp;
    }
}