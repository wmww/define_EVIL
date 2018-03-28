#include "define_EVIL.h"
#include <iostream>

#define EMPTY_MACRO
#define PUT_IN_BRAC(a, i) [i: a]
#define ADD_T(i) T_##i
#define COMMA ,

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
	
	std::cout << "IS_THING:" << std::endl;
	TEST_CASE_MACRO(IS_THING(a_thing), TRUE);
	TEST_CASE_MACRO(IS_THING("abc"), TRUE);
	TEST_CASE_MACRO(IS_THING("abc", 5, foo), TRUE);
	TEST_CASE_MACRO(IS_THING(, "abc", 5, foo), TRUE);
	TEST_CASE_MACRO(IS_THING(,,,,,,,,,,,a,,), TRUE);
	TEST_CASE_MACRO(IS_THING(()), TRUE);
	TEST_CASE_MACRO(IS_THING((a, "b")), TRUE);
	TEST_CASE_MACRO(IS_THING(a, ()), TRUE);
	TEST_CASE_MACRO(IS_THING((), "a", 9), TRUE);
	TEST_CASE_MACRO(IS_THING((), (), ()), TRUE);
	TEST_CASE_MACRO(IS_THING(), FALSE);
	TEST_CASE_MACRO(IS_THING(EMPTY_MACRO), FALSE);
	TEST_CASE_MACRO(IS_THING(,,,,,,,,,,,,,), FALSE);
	std::cout << std::endl;
	
	std::cout << "HAS_PEREN:" << std::endl;
	TEST_CASE_MACRO(HAS_PEREN(), FALSE);
	TEST_CASE_MACRO(HAS_PEREN(a), FALSE);
	TEST_CASE_MACRO(HAS_PEREN("a"), FALSE);
	TEST_CASE_MACRO(HAS_PEREN(1, "a"), FALSE);
	TEST_CASE_MACRO(HAS_PEREN(ORDER_FWD_2), FALSE);
	TEST_CASE_MACRO(HAS_PEREN(()), TRUE);
	TEST_CASE_MACRO(HAS_PEREN(((a))), TRUE);
	TEST_CASE_MACRO(HAS_PEREN((1, "a", ())), TRUE);
	TEST_CASE_MACRO(HAS_PEREN((), 1, "a"), FALSE);
	std::cout << std::endl;
	
	std::cout << "GET_ITEM:" << std::endl;
	TEST_CASE_MACRO(GET_ITEM(PUT_IN_BRAC, FIRST), PUT_IN_BRAC);
	TEST_CASE_MACRO(GET_ITEM(PUT_IN_BRAC, SECOND), );
	TEST_CASE_MACRO(GET_ITEM((PUT_IN_BRAC, |), FIRST), PUT_IN_BRAC);
	TEST_CASE_MACRO(GET_ITEM((PUT_IN_BRAC, |), SECOND), |);
	std::cout << std::endl;
	
	std::cout << "REPEAT:" << std::endl;
	TEST_CASE_MACRO(REPEAT(ADD_T, 0), );
	TEST_CASE_MACRO(REPEAT(ADD_T, 1), T_0);
	TEST_CASE_MACRO(REPEAT(ADD_T, 4), T_0 T_1 T_2 T_3);
	TEST_CASE_MACRO(REPEAT_DOWN(ADD_T, 0), );
	TEST_CASE_MACRO(REPEAT_DOWN(ADD_T, 1), T_0);
	TEST_CASE_MACRO(REPEAT_DOWN(ADD_T, 4), T_3 T_2 T_1 T_0);
	TEST_CASE_MACRO(REPEAT((ADD_T, |), 0), );
	TEST_CASE_MACRO(REPEAT((ADD_T, |), 1), T_0);
	TEST_CASE_MACRO(REPEAT((ADD_T, |), 4), T_0 | T_1 | T_2 | T_3);
	TEST_CASE_MACRO(REPEAT_DOWN((ADD_T, |), 0), );
	TEST_CASE_MACRO(REPEAT_DOWN((ADD_T, |), 1), T_0);
	TEST_CASE_MACRO(REPEAT_DOWN((ADD_T, |), 4), T_3 | T_2 | T_1 | T_0);
	std::cout << std::endl;
	
	std::cout << "MAP:" << std::endl;
	
	TEST_CASE_MACRO(MAP(PUT_IN_BRAC, a, b, c, d), [0: a] [1: b] [2: c] [3: d]);
	TEST_CASE_MACRO(MAP(PUT_IN_BRAC, a), [0: a]);
	TEST_CASE_MACRO(MAP(PUT_IN_BRAC), );

	TEST_CASE_MACRO(MAP_REVERSE(PUT_IN_BRAC, a, b, c, d), [0: d] [1: c] [2: b] [3: a]);
	TEST_CASE_MACRO(MAP_REVERSE(PUT_IN_BRAC, a), [0: a]);
	TEST_CASE_MACRO(MAP_REVERSE(PUT_IN_BRAC), );

	TEST_CASE_MACRO(MAP_DOWN(PUT_IN_BRAC, a, b, c, d), [3: a] [2: b] [1: c] [0: d]);
	TEST_CASE_MACRO(MAP_DOWN(PUT_IN_BRAC, a), [0: a]);
	TEST_CASE_MACRO(MAP_DOWN(PUT_IN_BRAC), );

	TEST_CASE_MACRO(MAP_REVERSE_DOWN(PUT_IN_BRAC, a, b, c, d), [3: d] [2: c] [1: b] [0: a]);
	TEST_CASE_MACRO(MAP_REVERSE_DOWN(PUT_IN_BRAC, a), [0: a]);
	TEST_CASE_MACRO(MAP_REVERSE_DOWN(PUT_IN_BRAC), );
	
	TEST_CASE_MACRO(MAP((PUT_IN_BRAC, |), a, b, c, d), [0: a] | [1: b] | [2: c] | [3: d]);
	TEST_CASE_MACRO(MAP((PUT_IN_BRAC, |), a), [0: a]);
	TEST_CASE_MACRO(MAP((PUT_IN_BRAC, |)), );

	TEST_CASE_MACRO(MAP_REVERSE((PUT_IN_BRAC, |), a, b, c, d), [0: d] | [1: c] | [2: b] | [3: a]);
	TEST_CASE_MACRO(MAP_REVERSE((PUT_IN_BRAC, |), a), [0: a]);
	TEST_CASE_MACRO(MAP_REVERSE((PUT_IN_BRAC, |)), );

	TEST_CASE_MACRO(MAP_DOWN((PUT_IN_BRAC, |), a, b, c, d), [3: a] | [2: b] | [1: c] | [0: d]);
	TEST_CASE_MACRO(MAP_DOWN((PUT_IN_BRAC, |), a), [0: a]);
	TEST_CASE_MACRO(MAP_DOWN((PUT_IN_BRAC, |)), );

	TEST_CASE_MACRO(MAP_REVERSE_DOWN((PUT_IN_BRAC, -), a, b, c, d), [3: d] - [2: c] - [1: b] - [0: a]);
	TEST_CASE_MACRO(MAP_REVERSE_DOWN((PUT_IN_BRAC, -), a), [0: a]);
	TEST_CASE_MACRO(MAP_REVERSE_DOWN((PUT_IN_BRAC, -)), );
	std::cout << std::endl;
	
	std::cout << "COUNT:" << std::endl;
	TEST_CASE_MACRO(COUNT(), 0);
	TEST_CASE_MACRO(COUNT(a), 1);
	TEST_CASE_MACRO(COUNT(a, b), 2);
	TEST_CASE_MACRO(COUNT(a, b, c), 3);
	TEST_CASE_MACRO(COUNT(EMPTY_MACRO), 0);
	TEST_CASE_MACRO(COUNT("abc", 2, fsdafds, ()), 4);
	std::cout << std::endl;
	
	return 0;
}
