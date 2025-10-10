#!/bin/bash

# this script tests a planning server running on SERVER:PORT
# it is intended to be run from a test suite (compare file planningpokerservertests.c)

SERVER=$1
PORT=$2

declare -i GLOBAL_RET=0

estimate_and_assert() 
{
    estimate $1 $2
    assert_estimation $2 $3
}

estimate() 
{
    ESTIMATED_VALUE=$1
    ITEMID=$2
    response=$(printf "ESTIMATE\n$ITEMID\n$ESTIMATED_VALUE\0" | netcat -W 1 $SERVER $PORT)
    if [ "$response" != "OK" ]; then
        echo "Did not receive expected response OK. Intead got $response. \n"
        return 1;
    else
        return 0;
    fi
}

assert_estimation() 
{
    ITEMID=$1;
    EXPECTED_RES=$2;
    response=$(printf "GETRESULT\n$ITEMID\0" | netcat -W 1 $SERVER $PORT)
    ret=0
    if [ "$response" = "$EXPECTED_RES" ]; then
        ret=0
    else 
        echo "Did not receive expected value $EXPECTED_RES of estimations. Instead got $response. \n"
        ret=1
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

estimate_and_assert 10 ITEM1 10
estimate_and_assert 4 ITEM2 4
estimate_and_assert 56 ITEM3 56
estimate_and_assert 67 ITEM4 67
estimate_and_assert 78 ITEM5 78

estimate 10 ITEM6
estimate 34 ITEM6
estimate 45 ITEM6
assert_estimation ITEM6 '10|34|45'

exit $GLOBAL_RET