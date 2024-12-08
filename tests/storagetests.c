#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <sqlite3.h>
#include <stdio.h>
#include "../headers/storage.h"

int __wrap_sqlite3_open(char *filename, sqlite3 *db) 
{ 
    check_expected(filename);
    check_expected(db);
    return (int)mock();
}

int __wrap_sqlite3_exec(sqlite3 *db, char *sql, int (*callback)(void *, int, char **, char **), void *calbpara, char **errmsg) 
{
    check_expected(db);
    check_expected(sql);
    check_expected(callback);
    check_expected(calbpara);
    check_expected(errmsg);

    return (int)mock();
}

int __wrap_sqlite3_close(sqlite3 *db) 
{
    check_expected(db);
    return (int)mock();
}

void __wrap_fwarnf(char *format, va_list ap) 
{
    fprintf(stdout, "Hello my friend \n");
    check_expected(format);
    check_expected(ap);
}

static void store_estimation_cannot_open_db(void **state) 
{
    will_return(__wrap_sqlite3_open, 1);
    expect_any(__wrap_sqlite3_open, filename);
    expect_any(__wrap_sqlite3_open, db);

    int ret = store_estimation("ITEM", 12);

    assert_int_equal(ret, 1);
}

static void store_estimation_cannot_execute_query(void **state) 
{
    will_return(__wrap_sqlite3_open, 0);
    expect_any(__wrap_sqlite3_open, filename);
    expect_any(__wrap_sqlite3_open, db);
    will_return(__wrap_sqlite3_exec, 1);
    expect_any(__wrap_sqlite3_exec, db);
    expect_any(__wrap_sqlite3_exec, sql);
    expect_any(__wrap_sqlite3_exec, callback);
    expect_any(__wrap_sqlite3_exec, calbpara);
    expect_any(__wrap_sqlite3_exec, errmsg);
    will_return(__wrap_sqlite3_close, 0);
    expect_any(__wrap_sqlite3_close, db);
    
    int ret = store_estimation("ITEM", 12);

    assert_int_equal(ret, 1);
}

static void store_estimation_good_case(void **state) 
{
    will_return(__wrap_sqlite3_open, 0);
    expect_any(__wrap_sqlite3_open, filename);
    expect_any(__wrap_sqlite3_open, db);
    will_return(__wrap_sqlite3_exec, 0);
    expect_any(__wrap_sqlite3_exec, db);
    expect_any(__wrap_sqlite3_exec, sql);
    expect_any(__wrap_sqlite3_exec, callback);
    expect_any(__wrap_sqlite3_exec, calbpara);
    expect_any(__wrap_sqlite3_exec, errmsg);
    will_return(__wrap_sqlite3_close, 0);
    expect_any(__wrap_sqlite3_close, db);  
    
    int ret = store_estimation("ITEM", 12);

    assert_int_equal(ret, 0);
}

static void store_estimation_canot_close_database_generates_warning(void **state) 
{
    will_return(__wrap_sqlite3_open, 0);
    expect_any(__wrap_sqlite3_open, filename);
    expect_any(__wrap_sqlite3_open, db);
    will_return(__wrap_sqlite3_exec, 0);
    expect_any(__wrap_sqlite3_exec, db);
    expect_any(__wrap_sqlite3_exec, sql);
    expect_any(__wrap_sqlite3_exec, callback);
    expect_any(__wrap_sqlite3_exec, calbpara);
    expect_any(__wrap_sqlite3_exec, errmsg);
    will_return(__wrap_sqlite3_close, 1);
    expect_any(__wrap_sqlite3_close, db);
    expect_any(__wrap_fwarnf ,format);
    expect_any(__wrap_fwarnf, ap);
    
    int ret = store_estimation("ITEM", 12);

    assert_int_equal(ret, 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(store_estimation_cannot_open_db),
        cmocka_unit_test(store_estimation_cannot_execute_query),
        cmocka_unit_test(store_estimation_good_case),
        cmocka_unit_test(store_estimation_canot_close_database_generates_warning)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}

