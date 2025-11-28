#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "../headers/handler.h"
#include <sqlite3.h>

static void estimate_item_once(void **state) 
{
    assert_int_equal(system("./tests/testplanningserver.sh 127.0.0.3 1234"), 0);
}

static void start_session(void **state) 
{
    assert_int_equal(system("./tests/testplanningserversession.sh 127.0.0.3 1234"), 0);
}

static int clean_db(void **state) 
{
    sqlite3 *db;
    char *zErrMsg = 0;
    char *dbname = "./database/planningpoker.db";
    int rc = sqlite3_open(dbname, &db);
    if(rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    int ret = 0;
    rc = sqlite3_exec(db, "DELETE FROM ESTIMATION", NULL, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        ret = 1; 
    }

    rc = sqlite3_close(db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot close database %s.", dbname);
        ret = 1;
    }
    return ret;
}

int main(void) 
{
    const struct CMUnitTest tests[] = {
        cmocka_unit_test_setup_teardown(estimate_item_once, clean_db, clean_db),
        cmocka_unit_test_setup_teardown(start_session, clean_db, clean_db),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}