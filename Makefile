.PHONY: build

build:
	cc -Wall -o planningpokerserver.out planningpokerserver.c handler.c storage.c -lsqlite3 -lm

test: build testhandler
	cc -Wall -o planningpokerservertests.out ./tests/planningpokerservertests.c handler.c storage.c -lcmocka -lm -lsqlite3
	./planningpokerserver.out &
	./planningpokerservertests.out || true
	pkill planningpokerse

testhandler:
	cc -Wall -o handlertests.out ./tests/handlertests.c handler.c storage.c -lcmocka -lsqlite3 -lm -Wl,--wrap=store_estimation,--wrap=get_estimations
	./handlertests.out

sqliteint:
	cc -Wall -o planningpokerserver.out planningpokerserver.c -lsqlite3

