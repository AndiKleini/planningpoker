#include <stdlib.h>
#include <stdio.h>
#include "./headers/handler.h"
#include "./headers/storage.h"
#include <string.h>
#include <math.h>

struct response * process_request(char* buffer)
{
    char *cmd = strtok(buffer, "\n");
    if (strcmp(cmd, "ESTIMATE") == 0) {
        char *itemId = strtok(NULL, "\n");
        store_estimation(itemId, atoi(strtok(NULL, "\n")));
        struct response *resp = (struct response *)malloc(sizeof(struct response));
        resp->msg = "OK";
        resp->size = 2;
        return resp;
    } else if(strcmp(cmd, "STARTESTIMATION") == 0) {
        char *itemId = strtok(NULL, "\n");
        struct response *resp = (struct response *)malloc(sizeof(struct response));
        resp->msg = store_session(itemId);
        resp->size = strlen(resp->msg);
        return resp;
    } else {
        struct response *resp = (struct response *)malloc(sizeof(struct response));
        char *itemId = strtok(NULL, "\n");
        resp->msg = get_estimations(itemId);
        resp->size = strlen(resp->msg);
        return resp;
    }
}