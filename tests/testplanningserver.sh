#!/bin/sh

SERVER=$1
PORT=$2

declare -i GLOBAL_RET=0

estimate_and_query() 
{
    ESTIMATED_VALUE=$1
    ITEMID=$2
    EXPECTED_RES=$3
    response=$(printf "ESTIMATE\n$ITEMID\n$ESTIMATED_VALUE\0" | netcat -W 1 $SERVER $PORT)
    echo $response
    if [ "$response" != "OK" ]; then
        echo "Did not receive expected response OK. Intead got $response. \n"
        return 1;
    fi

    response=$(printf "GETRESULT\n$ITEMID\0" | netcat -W 1 $SERVER $PORT)
    echo $response
    ret=0
    if [ "$response" = "$EXPECTED_RES" ]; then
        ret=0
    else 
        echo "Did not receive expected value $EXPECTED_RES of estimations. Intead got $response. \n"
        ret=1
    fi
    GLOBAL_RET=$(($GLOBAL_RET + $ret));
    return $ret
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

estimate_and_query 10 ITEM1 10
estimate_and_query 4 ITEM2 4
estimate_and_query 56 ITEM3 56
estimate_and_query 67 ITEM4 67
estimate_and_query 78 ITEM5 78
return $GLOBAL_RET
