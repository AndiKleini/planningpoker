#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <setjmp.h>
#include <cmocka.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/handler.h"

static void estimate_item_once(void **state) {
    assert_int_equal(system("./tests/testplanningserver.sh 127.0.0.3 1234"), 0);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(estimate_item_once),
    };
    return cmocka_run_group_tests(tests, NULL, NULL);
}
