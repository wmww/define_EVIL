#ifndef EVIL
#define EVIL

// macros auto-generated from autogen.sh
// should all be prefixed with _AG_
#include "autogen.h"

/// General Utils

// convert input to string literal, can be used with EXPAND_CALL
// depends on: none
#define TO_STRING(a) #a

// used internally by other macros
#define ORDER_FWD_2(a, b) a b
#define ORDER_BKWD_2(a, b) b a
#define ORDER_FWD_3(a, b, c) a b c
#define ORDER_BKWD_3(a, b, c) c b a

// expands the arguments and concatenates them
// depends on: none
#define EXPAND_CAT(a, ...) _EXPAND_CAT(a, __VA_ARGS__)
#define _EXPAND_CAT(a, ...) a##__VA_ARGS__

// expands the arguments and then call macro with the expanded arguments
// depends on: none
#define EXPAND_CALL(macro, ...) macro(__VA_ARGS__)

// even I'm not completely sure why this is needed, but it is.
#define EXPAND(...) __VA_ARGS__

// removes commas in a list of arguments, leaves a space between each one
// depends on: _AG_REMOVE_COMMAS_...
#define REMOVE_COMMAS(...) _AG_REMOVE_COMMAS_0(__VA_ARGS__)

// CHECK_IF_THING(one_or_more, args)	-> A_THING
// CHECK_IF_THING()						-> NOTHING
// NOTE: the final arg can not be the name of a function-like macro!
// a common way to use is to make two macros (ex. EXAMPLE_A_THING and EXAMPLE_NOTHING) and concat your prefix with the
// result of this macro, so you can do different things depending on the thingyness
// the last argument must not be a function-like macro
// depends on: EXPAND_CALL, EXPAND_CAT, EXPAND
// I realize how much of a clusterfuck this is. If you can make it cleaner without failing any tests, plz submit PR
#define CHECK_IF_THING(...) _CHECK_IF_THING_A(EXPAND_CAT(_, EXPAND(_CHECK_IF_THING_D REMOVE_COMMAS(__VA_ARGS__))))
#define _CHECK_IF_THING_A(a) EXPAND_CALL(_CHECK_IF_THING_C, _CHECK_IF_THING_B a (), A_THING)
#define _CHECK_IF_THING_B() dummy, NOTHING
#define _CHECK_IF_THING_C(a, b, ...) b
#define _CHECK_IF_THING_D(...) dummy
#define __CHECK_IF_THING_D

// checks if the argument(s) are completely surrounded by parenthesis
// CHECK_FOR_PEREN() -> NO_PEREN
// CHECK_FOR_PEREN("a") -> NO_PEREN
// CHECK_FOR_PEREN(6, "a") -> NO_PEREN
// CHECK_FOR_PEREN(()) -> HAS_PEREN
// CHECK_FOR_PEREN((a, 6, "a")) -> HAS_PEREN
// will cause error if no peren but the first args is peren pair (ex below)
// CHECK_FOR_PEREN((), a, 6, "a") -> should be NO_PEREN but will throw error
// depends on: EXPAND_CAT, EXPAND
#define CHECK_FOR_PEREN(...) _CHECK_FOR_PEREN_C(EXPAND(_CHECK_FOR_PEREN_A __VA_ARGS__))
#define _CHECK_FOR_PEREN_A(...) _CHECK_FOR_PEREN_B
#define _OTHER_CHECK_FOR_PEREN_A _NO_PEREN(
#define _OTHER_CHECK_FOR_PEREN_B _HAS_PEREN(
#define _CHECK_FOR_PEREN_C(...) EXPAND_CAT(_OTHER, __VA_ARGS__) )
#define _NO_PEREN(...) NO_PEREN
#define _HAS_PEREN() HAS_PEREN

// expands to the number of arguments; empty arguments are counted; zero arguments is handeled correctly
// the last argument must not be a function-like macro
// expands to the number of arguments; empty arguments are counted; zero arguments is handled correctly
// depends on: EXPAND_CAT, EXPAND_CALL, CHECK_IF_THING, _AG_COUNT_THINGS, _AG_COUNT_THINGS_NUMBERS
#define COUNT_THINGS(...) EXPAND_CAT(_COUNT_THINGS_, CHECK_IF_THING(__VA_ARGS__))(__VA_ARGS__)
#define _COUNT_THINGS_NOTHING(...) 0
#define _COUNT_THINGS_A_THING(...) EXPAND_CALL(_AG_COUNT_THINGS, __VA_ARGS__, _AG_COUNT_THINGS_NUMBERS)

// GET_ITEM(abc, FIRST) -> abc
// GET_ITEM(abc, SECOND) -> [empty]
// GET_ITEM((abc, xyz), FIRST) -> abc
// GET_ITEM((abc, xyz), SECOND) -> xyz
// specalized to be used with REPEAT and MAP, may be more generalized later
#define GET_ITEM(func, item) EXPAND_CAT(_GET_ITEM_, CHECK_FOR_PEREN(func)) (func, item)
#define _GET_ITEM_HAS_PEREN(func, item) _GET_ITEM_HAS_PEREN_##item func
#define _GET_ITEM_HAS_PEREN_FIRST(macro, joiner) macro
#define _GET_ITEM_HAS_PEREN_SECOND(macro, joiner) joiner
#define _GET_ITEM_NO_PEREN(func, item) _GET_ITEM_NO_PEREN_##item (func)
#define _GET_ITEM_NO_PEREN_FIRST(func) func
#define _GET_ITEM_NO_PEREN_SECOND(func)

#define REPEAT(func, count) _AG_REPEAT_##count(GET_ITEM(func, FIRST), GET_ITEM(func, SECOND), ORDER_FWD_3)
#define REPEAT_DOWN(func, count) _AG_REPEAT_##count(GET_ITEM(func, FIRST), GET_ITEM(func, SECOND), ORDER_BKWD_3)

// applies the given macro to all additional arguments
// macro should accept item and index
// MAP_DOWN: indexes count down to 0 instead of up from 0
// MAP_REVERSE: items are in reverse order
// MAP_REVERSE_DOWN: both
// depends on: EXPAND_CAT, COUNT_THINGS, CHECK_FOR_PEREN, INC_.. (auto generated), DEC_.. (auto generated)
#define MAP(func, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(GET_ITEM(func, FIRST), GET_ITEM(func, SECOND), ORDER_FWD_3, 0, INC_, __VA_ARGS__)
#define MAP_DOWN(func, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(GET_ITEM(func, FIRST), GET_ITEM(func, SECOND), ORDER_FWD_3, EXPAND_CAT(DEC_, COUNT_THINGS(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE(func, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(GET_ITEM(func, FIRST), GET_ITEM(func, SECOND), ORDER_BKWD_3, EXPAND_CAT(DEC_, COUNT_THINGS(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE_DOWN(func, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(GET_ITEM(func, FIRST), GET_ITEM(func, SECOND), ORDER_BKWD_3, 0, INC_, __VA_ARGS__)

// Tests

// tests if the input expression matches the expected value and prints result
// depends on:  none
#define TEST_CASE(expr, expected) _TEST_CASE_A(#expr, expr, expected)

// like TEST_CASE, but for when you are testing a macro expression
// depends on:  EXPAND_CALL, TO_STRING
#define TEST_CASE_MACRO(macro_expr, expected) _TEST_CASE_A(#macro_expr, EXPAND_CALL(TO_STRING, macro_expr), #expected)

#define _TEST_CASE_A(expr_str, result, expected) { \
	const bool success = (result == expected); \
	std::cout << (success ? " .  " : " X  ") << expr_str << ": " << result; \
	if (!success) { \
		std::cout << " (" << expected << " expected)"; \
	} \
	std::cout << std::endl; \
}

#endif // EVIL
