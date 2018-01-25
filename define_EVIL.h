#ifndef EVIL
#define EVIL

// macros auto-generated from auto_gen.sh
// should all be prefixed with AG_
#include "auto_gen.h"

/// General Utils

// convert input to string literal, can be used with EXPAND_CALL
#define TO_STRING(a) #a

// expands the arguments and concatinates them
#define EXPAND_CAT(a, b) _EXPAND_CAT(a, b)
#define _EXPAND_CAT(a, b) a##b

// returns the first argument
// #define GET_FIRST_ARG(first, ...) first

// expands the arguments and then call macro with the expanded arguments
#define EXPAND_CALL(macro, ...) macro(__VA_ARGS__)

// removes commas in a list of arguments, leaves a space between each one
#define REMOVE_COMMAS(...) _AG_REMOVE_COMMAS_0(__VA_ARGS__)

// for print('#define _REMOVE_COMMAS_' + str(i) + '(a, ...) a _REMOVE_COMMAS_' + str(i) + '(__VA_ARGS__)')

// CHECK_IF_THING(one_or_more, args)	-> A_THING
// CHECK_IF_THING()					-> NOTHING
// a common way to use is to make two macros (ex. EXAMPLE_A_THING and EXAMPLE_NOTHING) and concat your prefix with the
// result of this macro, so you can do different things depending on the thingyness
#define CHECK_IF_THING(...) _CHECK_IF_THING_A(REMOVE_COMMAS(__VA_ARGS__))
#define _CHECK_IF_THING_A(a) EXPAND_CALL(_CHECK_IF_THING_C, _CHECK_IF_THING_B a (), A_THING)
#define _CHECK_IF_THING_B() dummy, NOTHING
#define _CHECK_IF_THING_C(a, b, ...) b

// CHECK_FOR_PEREN() -> NO_PEREN
// CHECK_FOR_PEREN("a") -> NO_PEREN
// CHECK_FOR_PEREN(()) -> HAS_PEREN
// CHECK_FOR_PEREN((a, 6, "a")) -> HAS_PEREN
#define CHECK_FOR_PEREN(a) EXPAND_CAT(_NOT, _PEREN_FOUND a) )
#define _PEREN_FOUND(...) _DOES_HAVE_PEREN(
#define _NOT_PEREN_FOUND _NO_PEREN(
#define _NO_PEREN(...) NO_PEREN
#define _NOT_DOES_HAVE_PEREN(...) HAS_PEREN

// expands to the number of arguments; empty arguments are counted; zero arguments is handeled correctly
#define COUNT_THINGS(...) EXPAND_CAT(_COUNT_THINGS_, CHECK_IF_THING(__VA_ARGS__))(__VA_ARGS__)
#define _COUNT_THINGS_NOTHING(...) 0
#define _COUNT_THINGS_A_THING(...) EXPAND_CALL(_AG_COUNT_THINGS, __VA_ARGS__, _AG_COUNT_THINGS_NUMBERS)

// applies the given macro to all additional arguments
// macro should accept item and index
// MAP_DOWN: indexes count down to 0 instead of up from 0
// MAP_REVERSE: items are in reverse order
// MAP_REVERSE_DOWN: both
#define MAP(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_FWD, 0, INC_, __VA_ARGS__)
#define MAP_DOWN(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_FWD, EXPAND_CAT(DEC_, COUNT_THINGS(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_BKWD, EXPAND_CAT(DEC_, COUNT_THINGS(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE_DOWN(macro, ...) EXPAND_CAT(_AG_MAP_, COUNT_THINGS(__VA_ARGS__))(macro, _MAP_BKWD, 0, INC_, __VA_ARGS__)
#define _MAP_FWD(a, b) a b
#define _MAP_BKWD(a, b) b a

// Tests

// tests if the input expression matches the expected value and prints result
#define TEST_CASE(expr, expected) _TEST_CASE_A(#expr, expr, expected)

// like TEST_CASE, but for when you are testing a macro expression
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
