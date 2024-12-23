# Planningpoker

This is planningpoker application that can be used for collaboarative estimations of working packages (e.g. user stories, tasks ...) within teams.
Each team member can submit an estimation. The application can afterwards emit the aggregated results.

## Client server connection

The server starts listening for incoming TCP connections on a particular port. Any TCP client can now send messages to the server. Check out following examples based on the netcat tool:

Submit and estimation:
`printf "ESTIMATE\nITEM1\n134\0" | netcat -W 1 127.0.0.3 1234`

Query results to an estimation:
`printf "GETRESULT\nITEM1\0" | netcat -W 1 127.0.0.3 1234`

## Techstack characteristics

- The tool is build on C socket api for LINUX. 

- As database SQLITE was selected.

- Basic architecture style is layered with layers planningpokerserver, handler and storage.

- The underlying protocol can be viewed  [here](./architecture/protocoldef.md)

- unit tests written in cmocka

- automated component tests by shell script using **netcat** as TCP client and **ss** for socket inspection. The script is launched by a proper cmocka unit tests and there for runs as test suit.

## Methodology
The tool was created following TDD approach.

## Deployment
[Makefile](./Makefile) supports with target **test** an automated testrun. With **build** the server deployables can be created.




