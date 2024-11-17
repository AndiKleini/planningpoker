#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../headers/handler.h"

int __wrap_store_estimation(char *itemId, int value) {
    check_expected(itemId);
    check_expected(value);
    return (int)mock();
}

char *__wrap_get_estimations(char *itemId) {
    check_expected(itemId);
    return (char *)mock();
}

static void process_single_request_of_estimation_and_query(void **state) {
    will_return(__wrap_store_estimation, 0);
    expect_string(__wrap_store_estimation, itemId, "ITEM1");
    expect_value(__wrap_store_estimation, value, 12);
    will_return(__wrap_get_estimations, "12\n\0");
    expect_string(__wrap_get_estimations, itemId, "ITEM1");
    char reqest[] = "ESTIMATE\nITEM1\n12\0";
    assert_string_equal(process_request(reqest)->msg, "OK\0");
    char reqquery[] = "GETRESULT\nITEM1\0";
    assert_string_equal(process_request(reqquery)->msg, "12\n\0");

}

static void process_multiple_requests_of_estimation_and_query(void **state) {
    will_return(__wrap_store_estimation, 0);
    expect_string(__wrap_store_estimation, itemId, "ITEM1");
    expect_value(__wrap_store_estimation, value, 12);
    will_return(__wrap_store_estimation, 0);
    expect_string(__wrap_store_estimation, itemId, "ITEM1");
    expect_value(__wrap_store_estimation, value, 23);
    will_return(__wrap_get_estimations, "12\n23\n\0");
    expect_string(__wrap_get_estimations, itemId, "ITEM1");
    char reqest[] = "ESTIMATE\nITEM1\n12\0";
    assert_string_equal(process_request(reqest)->msg, "OK\0");
    char reqest2nd[] = "ESTIMATE\nITEM1\n23\0";
    assert_string_equal(process_request(reqest2nd)->msg, "OK\0");
    char reqquery[] = "GETRESULT\nITEM1\0";
    assert_string_equal(process_request(reqquery)->msg, "12\n23\n\0");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(process_single_request_of_estimation_and_query),
        cmocka_unit_test(process_multiple_requests_of_estimation_and_query)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}