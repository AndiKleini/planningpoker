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

teststorage:
	cc -Wall -o storagetests.out ./tests/storagetests.c storage.c -lcmocka -lsqlite3 -lm -Wl,--wrap=sqlite3_open,--wrap=sqlite3_exec,--wrap=sqlite3_close,--wrap=sqlite3_close,--wrap=fprintf
	./storagetests.out

sqliteint:
	cc -Wall -o planningpokerserver.out planningpokerserver.c -lsqlite3

