#pragma once
 
struct response {
    char* msg;
    int size;
};

struct response * process_request(char* buffer);