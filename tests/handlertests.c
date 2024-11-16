#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include "../headers/handler.h"

static void process_request_of_estimation(void **state) {
    char req[] = "ESTIMATE\nITEM1\n12\0";
    assert_string_equal(process_request(req)->msg, "OK\0");
}

static void process_request_of_estimation_and_query(void **state) {
    char reqest[] = "ESTIMATE\nITEM1\n12\0";
    assert_string_equal(process_request(reqest)->msg, "OK\0");
    char reqquery[] = "GETRESULT\nITEM1\0";
    assert_string_equal(process_request(reqquery)->msg, "12\0");
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(process_request_of_estimation),
        cmocka_unit_test(process_request_of_estimation_and_query)
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}