#!/bin/bash

# this script tests a planning server running on SERVER:PORT
# it is intended to be run from a test suite (compare file planningpokerservertests.c)

SERVER=$1
PORT=$2
PORT2=$3

declare -i GLOBAL_RET=0
declare SESSION_ID=""

start_estimation() 
{
    ret=0;
    ESTIMATED_ITEMID=$1
    response=$(printf "STARTESTIMATION\n$ESTIMATED_ITEMID\0" | netcat -W 1 $SERVER $PORT)
    if [[ "$response" =~ ^[0-9]+ ]]; then
        SESSION_ID=$response
        ret=0;
    else
        echo "Did not receive expected response string consisting of digits only. Intead got $response. \n"
        ret=1;
    fi

    GLOBAL_RET=$(($GLOBAL_RET + $ret));
    return $ret
}

finish_estimation() 
{
    ret=0;
    response=$(printf "FINISHESTIMATION\n$SESSION_ID\0" | netcat -W 1 $SERVER $PORT2)
    if [ "$response" != "OK" ]; then
        echo "Did not receive expected response OK. Intead got $response. \n"
        ret=1 
    else
        ret=0
    fi

    GLOBAL_RET=$(($GLOBAL_RET + $ret));
    return $ret
}

# check wether the server is up and running  
which ss >/dev/null || (echo "Install ss tool first ! Script aborted here." && return 1)
which netcat >/dev/null || (echo "Install netcat first ! Script aborted here." && return 1)

ISLISTENING=$(which ss >/dev/null && ss -l | grep $PORT | wc -l)
if [ "$ISLISTENING" -eq "0" ]; then
    echo "Nothing is listening on $PORT !"
    return 1;
fi

start_estimation ITEM1
finish_estimation ITEM1

exit $GLOBAL_RET