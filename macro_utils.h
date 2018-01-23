#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

/// General Utils

// convert input to string literal, can be used with EXPAND_AND_CALL
#define TO_STRING(a) #a

// returns the first argument
#define GET_FIRST_ARG(first, ...) first

// expands the arguments and then call macro with the expanded arguments
#define EXPAND_AND_CALL(macro, ...) macro(__VA_ARGS__)

// usage: CHECK_IF_THING(any_single_arg)	-> A_THING
// usage: CHECK_IF_THING()					-> NOTHING
// a common way to use is to make two macros (ex. EXAMPLE_A_THING and EXAMPLE_NOTHING) and concat your prefix with the
// result of this macro, so you can do different things depending on the thingyness
#define _CHECK_IF_THING_A() dummy, NOTHING
#define _CHECK_IF_THING_B(a, b, ...) b
#define CHECK_IF_THING(a) EXPAND_AND_CALL(_CHECK_IF_THING_B, _CHECK_IF_THING_A a (), A_THING)

// Tests

// tests if the input expression matches the expected value and prints result
#define TEST_CASE(expr, expected) _TEST_CASE_A(#expr, expr, expected)

// like TEST_CASE, but for when you are testing a macro expression
#define TEST_CASE_MACRO(macro_expr, expected) _TEST_CASE_A(#macro_expr, EXPAND_AND_CALL(TO_STRING, macro_expr), #expected)

#define _TEST_CASE_A(expr_str, result, expected) { \
	const bool success = (result == expected); \
	std::cout << (success ? " .  " : " X  ") << expr_str << ": " << result; \
	if (!success) { \
		std::cout << " (" << expected << " expected)"; \
	} \
	std::cout << std::endl; \
}

#endif // MACRO_UTILS_H