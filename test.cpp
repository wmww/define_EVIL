#include "macro_utils.h"
#include <iostream>

int main()
{
	std::cout << "general utils:" << std::endl;
	#define XYZW xyzw
	TEST_CASE_MACRO(EXPAND_AND_CALL(TO_STRING, XYZW), "xyzw");
	TEST_CASE_MACRO(CHECK_IF_THING(a_thing), A_THING);
	TEST_CASE_MACRO(CHECK_IF_THING("abc"), A_THING);
	#define EMPTY_MACRO
	TEST_CASE_MACRO(CHECK_IF_THING(), NOTHING);
	TEST_CASE_MACRO(CHECK_IF_THING(EMPTY_MACRO), NOTHING);
	std::cout << std::endl;
	
	std::cout << "meta tests:" << std::endl;
	TEST_CASE(1 + 2, 3);
	TEST_CASE("foo", "foo");
	TEST_CASE("this is fine", "failure");
	TEST_CASE_MACRO(TO_STRING(abc), "abc");
	std::cout << std::endl;
	
	return 0;
}
