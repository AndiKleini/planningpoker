#Protocol of the pocker planner tool

Following commands will be supported:

* CONNECT
* LIST
* START 
* ESTIMATE
* GETRESULT
* RESTART (eventually)

## START (maybe obsolete)
Starts a new planningpoker session

```code
user@bar:~$ START\nThis should be the name of the item to vote about\n
```
Response:
ItemId (integer)

Error: Session already started

## ESTIMATE
Submits a vote for a particular item

example: ESTIMATE\nItemId\nValue

OK if successful otherwise returns ERROR. 
Errors:

* ItemId does not exist
* Value for Estimation not supported (e.g.: not an integer)

## GETRESULT
Displays the current state of the voting.

example: GETRESULT ItemId

Returns: "VotingResult1\nVotingResult2\nVotingResult3\n"


 
 
 

