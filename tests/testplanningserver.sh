#!/bin/sh

SERVER=$1
PORT=$2

estimate_and_query() 
{
    ESTIMATED_VALUE=$1
    response=$(printf "ESTIMATE\nITEM1\n$ESTIMATED_VALUE\0" | netcat -W 1 $SERVER $PORT)
    echo $response
    if [ "$response" != "OK" ]; then
        echo "Did not receive expected response OK. Intead got $response. \n"
        return 1;
    fi

    response=$(printf "GETRESULT\nITEM1\0" | netcat -W 1 $SERVER $PORT)
    echo $response
    if [ "$response" = "$ESTIMATED_VALUE" ]; then
        return 0;
    else 
        echo "Did not receive expected value $ESTIMATED_VALUE of estimations. Intead got $response. \n"
        return 1;
    fi
}

echo "Testing for open socket on localhost on port $PORT !"

# check wether the server is up and running  
which ss >/dev/null || (echo "Install ss tool first ! Script aborted here." && return 1)
which netcat >/dev/null || (echo "Install netcat first ! Script aborted here." && return 1)

ISLISTENING=$(which ss >/dev/null && ss -l | grep $PORT | wc -l)
if [ "$ISLISTENING" -gt "0" ]; then
    echo "Listening on $PORT succeeded !"
else 
    echo "Nothing is listening on $PORT !"
    return 1;
fi

estimate_and_query 10


