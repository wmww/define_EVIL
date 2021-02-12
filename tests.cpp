#include "define_EVIL.h"

#include <iostream>
#include <vector>
#include <string>

#define TEST_CASE_MACRO(macro_expr, ...) test_case(#macro_expr, EVIL_EXPAND_CALL(EVIL_TO_STRING, macro_expr), #__VA_ARGS__)

std::vector<std::string> failed_tests;

namespace color {
const char *normal = "\x1b[0m";
const char *green = "\x1b[1;32m";
const char *red = "\x1b[1;31m";
}

void test_case(std::string expr_str, std::string result, std::string expected) {
    using namespace color;
    const bool success = (result == expected);
    if (success)
        std::cout << green << " .  " << normal;
    else
        std::cout << red << " X  ";
    std::cout << expr_str << ": " << normal << result;
    if (!success) {
        std::cout << red << " | " << normal << expected << red << " expected" << normal;
        failed_tests.push_back({expr_str});
    }
    std::cout << std::endl;
}

// Returns true if all tests passed
bool show_final_result() {
    using namespace color;
    if (failed_tests.size() == 0) {
        std::cout << green << "All tests passed!" << normal << std::endl;
        return true;
    } else {
        std::cout << red << failed_tests.size() << " test" << (failed_tests.size() > 1 ? "s" : "") << " failed: " << normal;
        for (int i = 0; i < failed_tests.size(); i++) {
            std::cout << red << (i > 0 ? ", " : "") << normal << failed_tests[i];
        }
        std::cout << std::endl;
        return false;
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
    std::cout << std::endl;

    std::cout << "general utils:" << std::endl;
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
    std::cout << std::endl;

    std::cout << "EVIL_REMOVE_COMMAS:" << std::endl;
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(), );
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(abc), abc);
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(,), );
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS(a,b), a b);
    TEST_CASE_MACRO(EVIL_REMOVE_COMMAS("a",b, c,5   ,int*,,,8,), "a" b c 5 int* 8);
    std::cout << std::endl;

    std::cout << "Bools:" << std::endl;
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
    std::cout << std::endl;

    std::cout << "Conditionals:" << std::endl;
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
    std::cout << std::endl;

    std::cout << "Equality:" << std::endl;
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
    TEST_CASE_MACRO(EVIL_EQ(void, void), TRUE);
    TEST_CASE_MACRO(EVIL_EQ(void, 0), FALSE);
    TEST_CASE_MACRO(EVIL_EQ(xyz, xyz), "You must define EVIL_ENABLE_EQ_xyz_xyz to use EVIL_EQ on xyz");
    TEST_CASE_MACRO(EVIL_EQ(abc, xyz), "You must define EVIL_ENABLE_EQ_abc_abc to use EVIL_EQ on abc");
    TEST_CASE_MACRO(EVIL_NE(0, 1), TRUE);
    TEST_CASE_MACRO(EVIL_NE(0, 0), FALSE);
    std::cout << std::endl;

    std::cout << "EVIL_IS_THING:" << std::endl;
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
    std::cout << std::endl;

    std::cout << "HAS_PEREN:" << std::endl;
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
    std::cout << std::endl;

    std::cout << "REPEAT:" << std::endl;
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
    std::cout << std::endl;

    std::cout << "MAP:" << std::endl;

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
    std::cout << std::endl;

    std::cout << "COUNT:" << std::endl;
    TEST_CASE_MACRO(EVIL_COUNT(), 0);
    TEST_CASE_MACRO(EVIL_COUNT(a), 1);
    TEST_CASE_MACRO(EVIL_COUNT(a, b), 2);
    TEST_CASE_MACRO(EVIL_COUNT(a, b, c), 3);
    TEST_CASE_MACRO(EVIL_COUNT(EMPTY_MACRO), 0);
    TEST_CASE_MACRO(EVIL_COUNT("abc", 2, fsdafds, ()), 4);
    std::cout << std::endl;

    return show_final_result() ? 0 : 1;
}
