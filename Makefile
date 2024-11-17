.PHONY: build

build:
	cc -Wall -o planningpokerserver.out planningpokerserver.c handler.c storage.c -lsqlite3 -lm

test: build testhandler
	cc -Wall -o planningpokerservertests.out ./tests/planningpokerservertests.c handler.c storage.c -lcmocka -lm
	./planningpokerserver.out &
	./planningpokerservertests.out || true
	pkill planningpokerse

testhandler:
	cc -Wall -o handlertests.out ./tests/handlertests.c handler.c storage.c -lcmocka -lm
	./handlertests.out

sqliteint:
	cc -Wall -o planningpokerserver.out planningpokerserver.c -lsqlite3

