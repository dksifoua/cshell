#include "cshell/utils.h"

#include <cmocka.h>
#include <stdbool.h>
#include <string.h>

static void test_str_null_or_empty_null(void **state) {
    (void) state;
    assert_true(str_null_or_empty(nullptr));
}

static void test_str_null_or_empty_empty(void **state) {
    (void) state;
    assert_true(str_null_or_empty(""));
}

static void test_str_null_or_empty_whitespace_only(void **state) {
    (void) state;
    assert_true(str_null_or_empty("   "));
    assert_true(str_null_or_empty("\t \n"));
}

static void test_str_null_or_empty_non_empty(void **state) {
    (void) state;
    assert_false(str_null_or_empty("ls"));
    assert_false(str_null_or_empty("  a"));
}

static void test_remove_leading_whitespace_null(void **state) {
    (void) state;
    remove_leading_whitespace(nullptr);
}

static void test_remove_leading_whitespace_spaces(void **state) {
    (void) state;
    char input[] = "   echo hi";
    remove_leading_whitespace(input);
    assert_string_equal(input, "echo hi");
}

static void test_remove_leading_whitespace_tab_newline(void **state) {
    (void) state;
    char input[] = "\t\n ls";
    remove_leading_whitespace(input);
    assert_string_equal(input, "ls");
}

static void test_remove_leading_whitespace_no_leading(void **state) {
    (void) state;
    char input[] = "echo";
    remove_leading_whitespace(input);
    assert_string_equal(input, "echo");
}

static void test_remove_leading_whitespace_all_whitespace(void **state) {
    (void) state;
    char input[] = "   ";
    remove_leading_whitespace(input);
    assert_string_equal(input, "");
}

static void test_remove_trailing_newline_null(void **state) {
    (void) state;
    remove_trailing_newline(nullptr);
}

static void test_remove_trailing_newline_present(void **state) {
    (void) state;
    char input[] = "ls\n";
    remove_trailing_newline(input);
    assert_string_equal(input, "ls");
}

static void test_remove_trailing_newline_multiple(void **state) {
    (void) state;
    char input[] = "ls\n\n";
    remove_trailing_newline(input);
    assert_string_equal(input, "ls");
}

static void test_remove_trailing_newline_absent(void **state) {
    (void) state;
    char input[] = "ls";
    remove_trailing_newline(input);
    assert_string_equal(input, "ls");
}

static void test_remove_trailing_newline_only(void **state) {
    (void) state;
    char input[] = "\n";
    remove_trailing_newline(input);
    assert_string_equal(input, "");
}

int main(void) {
    disable_stdout_buffering();

    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_str_null_or_empty_null),
        cmocka_unit_test(test_str_null_or_empty_empty),
        cmocka_unit_test(test_str_null_or_empty_whitespace_only),
        cmocka_unit_test(test_str_null_or_empty_non_empty),
        cmocka_unit_test(test_remove_leading_whitespace_null),
        cmocka_unit_test(test_remove_leading_whitespace_spaces),
        cmocka_unit_test(test_remove_leading_whitespace_tab_newline),
        cmocka_unit_test(test_remove_leading_whitespace_no_leading),
        cmocka_unit_test(test_remove_leading_whitespace_all_whitespace),
        cmocka_unit_test(test_remove_trailing_newline_null),
        cmocka_unit_test(test_remove_trailing_newline_present),
        cmocka_unit_test(test_remove_trailing_newline_multiple),
        cmocka_unit_test(test_remove_trailing_newline_absent),
        cmocka_unit_test(test_remove_trailing_newline_only),
    };

    return cmocka_run_group_tests(tests, nullptr, nullptr);
}
