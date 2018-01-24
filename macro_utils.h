#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

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
#define REMOVE_COMMAS(...) _REMOVE_COMMAS_0(__VA_ARGS__)
// $ max=23; for i in $(seq 0 $max); do echo "#define _REMOVE_COMMAS_$i(a, ...) a _REMOVE_COMMAS_$[i + 1](__VA_ARGS__)"; done; echo "#define _REMOVE_COMMAS_$[max + 1](a, ...) a"

// for print('#define _REMOVE_COMMAS_' + str(i) + '(a, ...) a _REMOVE_COMMAS_' + str(i) + '(__VA_ARGS__)')

// usage: CHECK_IF_THING(one_or_more, args)	-> A_THING
// usage: CHECK_IF_THING()					-> NOTHING
// a common way to use is to make two macros (ex. EXAMPLE_A_THING and EXAMPLE_NOTHING) and concat your prefix with the
// result of this macro, so you can do different things depending on the thingyness
#define CHECK_IF_THING(...) _CHECK_IF_THING_A(REMOVE_COMMAS(__VA_ARGS__))
#define _CHECK_IF_THING_A(a) EXPAND_CALL(_CHECK_IF_THING_C, _CHECK_IF_THING_B a (), A_THING)
#define _CHECK_IF_THING_B() dummy, NOTHING
#define _CHECK_IF_THING_C(a, b, ...) b

#define COUNT_THINGS(...) EXPAND_CAT(_COUNT_THINGS_, CHECK_IF_THING(__VA_ARGS__))(__VA_ARGS__)
#define _COUNT_THINGS_NOTHING(...) 0
#define _COUNT_THINGS_A_THING(...) 1

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

// auto gen

#define _REMOVE_COMMAS_0(a, ...) a _REMOVE_COMMAS_1(__VA_ARGS__)
#define _REMOVE_COMMAS_1(a, ...) a _REMOVE_COMMAS_2(__VA_ARGS__)
#define _REMOVE_COMMAS_2(a, ...) a _REMOVE_COMMAS_3(__VA_ARGS__)
#define _REMOVE_COMMAS_3(a, ...) a _REMOVE_COMMAS_4(__VA_ARGS__)
#define _REMOVE_COMMAS_4(a, ...) a _REMOVE_COMMAS_5(__VA_ARGS__)
#define _REMOVE_COMMAS_5(a, ...) a _REMOVE_COMMAS_6(__VA_ARGS__)
#define _REMOVE_COMMAS_6(a, ...) a _REMOVE_COMMAS_7(__VA_ARGS__)
#define _REMOVE_COMMAS_7(a, ...) a _REMOVE_COMMAS_8(__VA_ARGS__)
#define _REMOVE_COMMAS_8(a, ...) a _REMOVE_COMMAS_9(__VA_ARGS__)
#define _REMOVE_COMMAS_9(a, ...) a _REMOVE_COMMAS_10(__VA_ARGS__)
#define _REMOVE_COMMAS_10(a, ...) a _REMOVE_COMMAS_11(__VA_ARGS__)
#define _REMOVE_COMMAS_11(a, ...) a _REMOVE_COMMAS_12(__VA_ARGS__)
#define _REMOVE_COMMAS_12(a, ...) a _REMOVE_COMMAS_13(__VA_ARGS__)
#define _REMOVE_COMMAS_13(a, ...) a _REMOVE_COMMAS_14(__VA_ARGS__)
#define _REMOVE_COMMAS_14(a, ...) a _REMOVE_COMMAS_15(__VA_ARGS__)
#define _REMOVE_COMMAS_15(a, ...) a _REMOVE_COMMAS_16(__VA_ARGS__)
#define _REMOVE_COMMAS_16(a, ...) a _REMOVE_COMMAS_17(__VA_ARGS__)
#define _REMOVE_COMMAS_17(a, ...) a _REMOVE_COMMAS_18(__VA_ARGS__)
#define _REMOVE_COMMAS_18(a, ...) a _REMOVE_COMMAS_19(__VA_ARGS__)
#define _REMOVE_COMMAS_19(a, ...) a _REMOVE_COMMAS_20(__VA_ARGS__)
#define _REMOVE_COMMAS_20(a, ...) a _REMOVE_COMMAS_21(__VA_ARGS__)
#define _REMOVE_COMMAS_21(a, ...) a _REMOVE_COMMAS_22(__VA_ARGS__)
#define _REMOVE_COMMAS_22(a, ...) a _REMOVE_COMMAS_23(__VA_ARGS__)
#define _REMOVE_COMMAS_23(a, ...) a _REMOVE_COMMAS_24(__VA_ARGS__)
#define _REMOVE_COMMAS_24(a, ...) a

#endif // MACRO_UTILS_H