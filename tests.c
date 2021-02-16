#include "define_EVIL.h"

#include <stdio.h>
#include <string.h>

#define TEST_CASE_MACRO(macro_expr, ...) test_case(__FILE__, __LINE__, #macro_expr, EVIL_EXPAND_CALL(EVIL_TO_STRING, macro_expr), #__VA_ARGS__)
#define COLOR_NORMAL "\x1b[0m"
#define COLOR_GREEN "\x1b[1;32m"
#define COLOR_RED "\x1b[1;31m"

int failed_tests_count = 0;
const char* failed_tests[1000];

void test_case(
    const char* file,
    int line,
    const char* expr_str,
    const char* result,
    const char* expected
) {
    const int success = (strcmp(result, expected) == 0);
    if (success)
        printf(COLOR_GREEN " .  ");
    else
        printf(COLOR_RED " X  ");
    printf(COLOR_NORMAL "%s: %s%s" COLOR_NORMAL, expr_str, success ? COLOR_GREEN : COLOR_RED, result);
    if (!success) {
        printf("\n");
        int padding = strlen(expr_str) - 4;
        for (int i = 0; i < padding; i++)
            printf(" ");
        printf("expected: " COLOR_RED "%s" COLOR_NORMAL "\n", expected);
        for (int i = 0; i < padding; i++)
            printf(" ");
        printf("at %s:%d", file, line);
        failed_tests[failed_tests_count] = expr_str;
        failed_tests_count++;
    }
    printf("\n");
}

// Returns true if all tests passed
int show_final_result() {
    if (failed_tests_count == 0) {
        printf(COLOR_GREEN "All tests passed!" COLOR_NORMAL "\n");
        return 1;
    } else {
        printf(
            COLOR_RED "%d test%s failed: " COLOR_NORMAL,
            failed_tests_count,
            failed_tests_count > 1 ? "s" : "");
        for (int i = 0; i < failed_tests_count; i++) {
            printf(
                COLOR_RED "%s" COLOR_NORMAL "%s",
                (i > 0 ? ", " : ""),
                failed_tests[i]);
        }
        printf("\n");
        return 0;
    }
}

#define EMPTY_MACRO
#define PUT_IN_BRAC(a, i) [i: a]
#define PUT_IN_BRAC_DIVIDER(a, i) EVIL_IF(EVIL_NOT(EVIL_EQ(0, i)))(|) [i: a]
#define PUT_IN_BRAC_DIVIDER_DOWN(a, i) [i: a] EVIL_IF(EVIL_NOT(EVIL_EQ(0, i)))(|)
#define ADD_T(i) T_##i
#define ADD_T_DIVIDER(i) EVIL_IF(EVIL_NOT(EVIL_EQ(0, i)))(|) T_##i
#define ADD_T_DIVIDER_DOWN(i) T_##i EVIL_IF(EVIL_NOT(EVIL_EQ(0, i)))(|)
#define COMMA ,

int main()
{
    printf("\ngeneral utils:\n");
    #define XYZW xyzw
    #define xyzw_a foo
    TEST_CASE_MACRO(EVIL_EXPAND_CALL(EVIL_TO_STRING, XYZW), "xyzw");
    TEST_CASE_MACRO(EVIL_EXPAND_CAT(XYZW, _a), foo);
    TEST_CASE_MACRO(EVIL_INC_0, 1);
    TEST_CASE_MACRO(EVIL_EXPAND_CAT(EVIL_INC_, EVIL_EXPAND_CAT(EVIL_INC_, 12)), 14);
    TEST_CASE_MACRO(EVIL_EXPAND_CAT(EVIL_INC_, 23), 24);
    TEST_CASE_MACRO(EVIL_EXPAND_CAT(EVIL_DEC_, 6), 5);
    TEST_CASE_MACRO(EVIL_EXPAND_CAT(EVIL_DEC_, 1), 0);
    TEST_CASE_MACRO(EVIL_EXPAND_CAT(EVIL_DEC_, 24), 23);
    TEST_CASE_MACRO(EVIL_EXPAND_TRUE(abc, xyz), abc, xyz);
    TEST_CASE_MACRO(EVIL_EXPAND_FALSE(abc, xyz), );
    printf("\n");

    printf("EVIL_REMOVE_COMMAS:\n");
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(), );
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(abc), abc);
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(,), );
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(a,b), a b);
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS("a",b, c,5   ,int*,,,8,), "a" b c 5 int* 8);
    printf("\n");

    printf("Bools:\n");
    TEST_CASE_MACRO(EVIL_NOT(TRUE), FALSE);
    TEST_CASE_MACRO(EVIL_NOT(FALSE), TRUE);
    TEST_CASE_MACRO(EVIL_OR(TRUE, TRUE), TRUE);
    TEST_CASE_MACRO(EVIL_OR(TRUE, FALSE), TRUE);
    TEST_CASE_MACRO(EVIL_OR(FALSE, TRUE), TRUE);
    TEST_CASE_MACRO(EVIL_OR(FALSE, FALSE), FALSE);
    TEST_CASE_MACRO(EVIL_AND(TRUE, TRUE), TRUE);
    TEST_CASE_MACRO(EVIL_AND(TRUE, FALSE), FALSE);
    TEST_CASE_MACRO(EVIL_AND(FALSE, TRUE), FALSE);
    TEST_CASE_MACRO(EVIL_AND(FALSE, FALSE), FALSE);
    TEST_CASE_MACRO(EVIL_XOR(TRUE, TRUE), FALSE);
    TEST_CASE_MACRO(EVIL_XOR(TRUE, FALSE), TRUE);
    TEST_CASE_MACRO(EVIL_XOR(FALSE, TRUE), TRUE);
    TEST_CASE_MACRO(EVIL_XOR(FALSE, FALSE), FALSE);
    TEST_CASE_MACRO(EVIL_NOT(EVIL_AND(EVIL_NOT(FALSE), FALSE)), TRUE);
    TEST_CASE_MACRO(EVIL_XOR(TRUE, TRUE), FALSE);
    TEST_CASE_MACRO(EVIL_XOR(EVIL_NOT(EVIL_AND(EVIL_NOT(FALSE), FALSE)), TRUE), FALSE);
    printf("\n");

    printf("Conditionals:\n");
    TEST_CASE_MACRO(EVIL_IF(TRUE)(), );
    TEST_CASE_MACRO(EVIL_IF(FALSE)(), );
    TEST_CASE_MACRO(EVIL_IF(TRUE)(abc()), abc());
    TEST_CASE_MACRO(EVIL_IF(FALSE)(abc()), );
    TEST_CASE_MACRO(EVIL_IF(TRUE)(x, y, z), x, y, z);
    TEST_CASE_MACRO(EVIL_IF(FALSE)(x, y, z), );
    TEST_CASE_MACRO(EVIL_IF(EVIL_NOT(TRUE))(a), );
    TEST_CASE_MACRO(EVIL_IF_NOT(FALSE)(a), a);
    TEST_CASE_MACRO(EVIL_IF(EVIL_XOR(EVIL_AND(EVIL_NOT(FALSE), FALSE), TRUE))(a), a);
    TEST_CASE_MACRO(EVIL_IF_ELSE(TRUE)()(), );
    TEST_CASE_MACRO(EVIL_IF_ELSE(FALSE)()(), );
    TEST_CASE_MACRO(EVIL_IF_ELSE(TRUE)(abc())(xyz()), abc());
    TEST_CASE_MACRO(EVIL_IF_ELSE(FALSE)(abc())(xyz()), xyz());
    TEST_CASE_MACRO(EVIL_IF_ELSE(TRUE)(x, y, z)(a, b, c), x, y, z);
    TEST_CASE_MACRO(EVIL_IF_ELSE(FALSE)(x, y, z)(a, b, c), a, b, c);
    TEST_CASE_MACRO(EVIL_IF_ELSE(EVIL_NOT(TRUE))(a)(b), b);
    TEST_CASE_MACRO(EVIL_IF_ELSE(EVIL_XOR(EVIL_AND(EVIL_NOT(FALSE), FALSE), TRUE))(a)(b), a);
    printf("\n");

    printf("Equality:\n");
    TEST_CASE_MACRO(EVIL_EQ(0, 1), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(1, 0), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(1, 1), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(0, 0), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(2, 2), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(6, 6), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(18, 18), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(18, 17), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(, 0), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(0, ), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(, ), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(TRUE, FALSE), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(FALSE, FALSE), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(TRUE, TRUE), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(EVIL_NOT(EVIL_OR(FALSE, FALSE)), TRUE), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(void, void), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(void, 0), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(xyz, xyz), "You must define EVIL_ENABLE_EQ_xyz_xyz to use EVIL_EQ on xyz");
    TEST_CASE_MACRO(EVIL_EQ(abc, xyz), "You must define EVIL_ENABLE_EQ_abc_abc to use EVIL_EQ on abc");
    TEST_CASE_MACRO(EVIL_NE(0, 1), TRUE);
    TEST_CASE_MACRO(EVIL_NE(0, 0), FALSE);
    printf("\n");

    printf("EVIL_IS_THING:\n");
    TEST_CASE_MACRO(EVIL_IS_THING(a_thing), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING("abc"), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING("abc", 5, foo), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING(, "abc", 5, foo), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING(,,,,,,,,,,,a,,), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING(()), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING((a, "b")), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING(a, ()), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING((), "a", 9), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING((), (), ()), TRUE);
    TEST_CASE_MACRO(EVIL_IS_THING(), FALSE);
    TEST_CASE_MACRO(EVIL_IS_THING(EMPTY_MACRO), FALSE);
    TEST_CASE_MACRO(EVIL_IS_THING(,,,,,,,,,,,,,), FALSE);
    printf("\n");

    printf("HAS_PEREN:\n");
    TEST_CASE_MACRO(EVIL_HAS_PEREN(), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(a), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN("a"), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(1, "a"), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(ORDER_FWD_2), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(()), TRUE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(((a))), TRUE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN((1, "a", ())), TRUE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN((), 1, "a"), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN((a) b), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(a (b)), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN((a) (b)), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN((a) c (b)), FALSE);

    // Test that it works with a function-like macro
    TEST_CASE_MACRO(EVIL_HAS_PEREN((PUT_IN_BRAC)), TRUE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN((a, PUT_IN_BRAC)), TRUE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(PUT_IN_BRAC), FALSE);
    TEST_CASE_MACRO(EVIL_HAS_PEREN(a, PUT_IN_BRAC), FALSE);
    printf("\n");

    printf("REPEAT:\n");
    TEST_CASE_MACRO(EVIL_REPEAT(ADD_T, 0), );
    TEST_CASE_MACRO(EVIL_REPEAT(ADD_T, 1), T_0);
    TEST_CASE_MACRO(EVIL_REPEAT(ADD_T, 4), T_0 T_1 T_2 T_3);
    TEST_CASE_MACRO(EVIL_REPEAT_DOWN(ADD_T, 0), );
    TEST_CASE_MACRO(EVIL_REPEAT_DOWN(ADD_T, 1), T_0);
    TEST_CASE_MACRO(EVIL_REPEAT_DOWN(ADD_T, 4), T_3 T_2 T_1 T_0);
    TEST_CASE_MACRO(EVIL_REPEAT(ADD_T_DIVIDER, 0), );
    TEST_CASE_MACRO(EVIL_REPEAT(ADD_T_DIVIDER, 1), T_0);
    TEST_CASE_MACRO(EVIL_REPEAT(ADD_T_DIVIDER, 4), T_0 | T_1 | T_2 | T_3);
    TEST_CASE_MACRO(EVIL_REPEAT_DOWN(ADD_T_DIVIDER_DOWN, 0), );
    TEST_CASE_MACRO(EVIL_REPEAT_DOWN(ADD_T_DIVIDER_DOWN, 1), T_0);
    TEST_CASE_MACRO(EVIL_REPEAT_DOWN(ADD_T_DIVIDER_DOWN, 4), T_3 | T_2 | T_1 | T_0);
    printf("\n");

    printf("MAP:\n");

    TEST_CASE_MACRO(EVIL_MAP(PUT_IN_BRAC, a, b, c, d), [0: a] [1: b] [2: c] [3: d]);
    TEST_CASE_MACRO(EVIL_MAP(PUT_IN_BRAC, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP(PUT_IN_BRAC), );

    TEST_CASE_MACRO(EVIL_MAP_REVERSE(PUT_IN_BRAC, a, b, c, d), [0: d] [1: c] [2: b] [3: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE(PUT_IN_BRAC, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE(PUT_IN_BRAC), );

    TEST_CASE_MACRO(EVIL_MAP_DOWN(PUT_IN_BRAC, a, b, c, d), [3: a] [2: b] [1: c] [0: d]);
    TEST_CASE_MACRO(EVIL_MAP_DOWN(PUT_IN_BRAC, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_DOWN(PUT_IN_BRAC), );

    TEST_CASE_MACRO(EVIL_MAP_REVERSE_DOWN(PUT_IN_BRAC, a, b, c, d), [3: d] [2: c] [1: b] [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE_DOWN(PUT_IN_BRAC, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE_DOWN(PUT_IN_BRAC), );

    TEST_CASE_MACRO(EVIL_MAP(PUT_IN_BRAC_DIVIDER, a, b, c, d), [0: a] | [1: b] | [2: c] | [3: d]);
    TEST_CASE_MACRO(EVIL_MAP(PUT_IN_BRAC_DIVIDER, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP(PUT_IN_BRAC_DIVIDER), );

    TEST_CASE_MACRO(EVIL_MAP_REVERSE(PUT_IN_BRAC_DIVIDER, a, b, c, d), [0: d] | [1: c] | [2: b] | [3: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE(PUT_IN_BRAC_DIVIDER, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE(PUT_IN_BRAC_DIVIDER), );

    TEST_CASE_MACRO(EVIL_MAP_DOWN(PUT_IN_BRAC_DIVIDER_DOWN, a, b, c, d), [3: a] | [2: b] | [1: c] | [0: d]);
    TEST_CASE_MACRO(EVIL_MAP_DOWN(PUT_IN_BRAC_DIVIDER_DOWN, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_DOWN(PUT_IN_BRAC_DIVIDER_DOWN), );

    TEST_CASE_MACRO(EVIL_MAP_REVERSE_DOWN(PUT_IN_BRAC_DIVIDER_DOWN, a, b, c, d), [3: d] | [2: c] | [1: b] | [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE_DOWN(PUT_IN_BRAC_DIVIDER_DOWN, a), [0: a]);
    TEST_CASE_MACRO(EVIL_MAP_REVERSE_DOWN(PUT_IN_BRAC_DIVIDER_DOWN), );
    printf("\n");

    printf("COUNT:\n");
    TEST_CASE_MACRO(EVIL_COUNT(), 0);
    TEST_CASE_MACRO(EVIL_COUNT(a), 1);
    TEST_CASE_MACRO(EVIL_COUNT(a, b), 2);
    TEST_CASE_MACRO(EVIL_COUNT(a, b, c), 3);
    TEST_CASE_MACRO(EVIL_COUNT(EMPTY_MACRO), 0);
    TEST_CASE_MACRO(EVIL_COUNT("abc", 2, fsdafds, ()), 4);
    printf("\n");

    return show_final_result() ? 0 : 1;
}
