#Protocol of the pocker planner tool

Following commands will be supported:

* ESTIMATE
* GETRESULT

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


 
 
 

