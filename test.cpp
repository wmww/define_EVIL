#include "define_EVIL.h"
#include <iostream>

#define EMPTY_MACRO

int main()
{
	std::cout << std::endl;
	
	std::cout << "general utils:" << std::endl;
	#define XYZW xyzw
	#define xyzw_a foo
	TEST_CASE_MACRO(EXPAND_CALL(TO_STRING, XYZW), "xyzw");
	TEST_CASE_MACRO(EXPAND_CAT(XYZW, _a), foo);
	TEST_CASE_MACRO(INC_0, 1);
	TEST_CASE_MACRO(EXPAND_CAT(INC_, EXPAND_CAT(INC_, 12)), 14);
	TEST_CASE_MACRO(EXPAND_CAT(INC_, 23), 24);
	TEST_CASE_MACRO(EXPAND_CAT(DEC_, 6), 5);
	TEST_CASE_MACRO(EXPAND_CAT(DEC_, 1), 0);
	TEST_CASE_MACRO(EXPAND_CAT(DEC_, 24), 23);
	std::cout << std::endl;
	
	std::cout << "REMOVE_COMMAS:" << std::endl;
	TEST_CASE_MACRO(REMOVE_COMMAS(), );
	TEST_CASE_MACRO(REMOVE_COMMAS(abc), abc);
	TEST_CASE_MACRO(REMOVE_COMMAS(,), );
	TEST_CASE_MACRO(REMOVE_COMMAS(a,b), a b);
	TEST_CASE_MACRO(REMOVE_COMMAS("a",b, c,5   ,int*,,,8,), "a" b c 5 int* 8);
	std::cout << std::endl;
	
	std::cout << "CHECK_IF_THING:" << std::endl;
	TEST_CASE_MACRO(CHECK_IF_THING(a_thing), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING("abc"), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING("abc", 5, foo), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING(, "abc", 5, foo), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING(,,,,,,,,,,,a,,), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING(), NOTHING);
	TEST_CASE_MACRO(CHECK_IF_THING(EMPTY_MACRO), NOTHING);
	TEST_CASE_MACRO(CHECK_IF_THING(,,,,,,,,,,,,,), NOTHING);
	std::cout << std::endl;
	
	std::cout << "MAP:" << std::endl;
	#define PUT_IN_BRAC(a, i) [i: a]
	TEST_CASE_MACRO(MAP_FWD_UP(PUT_IN_BRAC, a, b, c, d), [0: a] [1: b] [2: c] [3: d]);
	TEST_CASE_MACRO(MAP_FWD_UP(PUT_IN_BRAC, a), [0: a]);
	TEST_CASE_MACRO(MAP_FWD_UP(PUT_IN_BRAC), );
	std::cout << std::endl;
	
	std::cout << "COUNT_THINGS:" << std::endl;
	TEST_CASE_MACRO(COUNT_THINGS(), 0);
	TEST_CASE_MACRO(COUNT_THINGS(a), 1);
	TEST_CASE_MACRO(COUNT_THINGS(a, b), 2);
	TEST_CASE_MACRO(COUNT_THINGS(a, b, c), 3);
	TEST_CASE_MACRO(COUNT_THINGS(EMPTY_MACRO), 0);
	TEST_CASE_MACRO(COUNT_THINGS("abc", 2, fsdafds, ()), 4);
	std::cout << std::endl;
	
	return 0;
}
