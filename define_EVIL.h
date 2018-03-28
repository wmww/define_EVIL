#ifndef EVIL
#define EVIL

// macros auto-generated from autogen.sh
// should all be prefixed with _AG_
#include "generated.h"

/// General Utils

// convert input to string literal, can be used with EXPAND_CALL
// depends on: none
#define TO_STRING(...) #__VA_ARGS__

// used internally by other macros
#define ORDER_FORWARD(a, b) a b
#define ORDER_BACKWARD(a, b) b a

// expands the arguments and concatenates them
// depends on: none
#define EXPAND_CAT(a, ...) _EXPAND_CAT(a, __VA_ARGS__)
#define _EXPAND_CAT(a, ...) a##__VA_ARGS__

// expands the arguments and then call macro with the expanded arguments
// depends on: none
#define EXPAND_CALL(macro, ...) macro(__VA_ARGS__)
#define EXPAND_CALL_1(macro, a) macro(a)

// even I'm not completely sure why this is needed, but it is.
#define EXPAND(...) __VA_ARGS__

// toggleable expansion
#define EXPAND_TRUE(...) __VA_ARGS__
#define EXPAND_FALSE(...)

// removes commas in a list of arguments, leaves a space between each one
// depends on: _GEN_REMOVE_COMMAS_...
#define REMOVE_COMMAS(...) _GEN_REMOVE_COMMAS_0(__VA_ARGS__)

// BOOL
// expand to result of boolean logic (NOT(a), OR(a, b), AND(a, b), XOR(a, b))
// only defined for input TRUE and FALSE

#define NOT(...) _NOT(__VA_ARGS__)
#define _NOT(a) EXPAND_CAT(_BOOL_NOT_, a)
#define _BOOL_NOT_TRUE FALSE
#define _BOOL_NOT_FALSE TRUE

#define OR(...) _OR(__VA_ARGS__)
#define _OR(a, b) EXPAND_CAT(_BOOL_OR_, EXPAND_CAT(a, EXPAND_CAT(_, b)))
#define _BOOL_OR_FALSE_FALSE FALSE
#define _BOOL_OR_TRUE_FALSE TRUE
#define _BOOL_OR_FALSE_TRUE TRUE
#define _BOOL_OR_TRUE_TRUE TRUE

#define AND(...) _AND(__VA_ARGS__)
#define _AND(a, b) EXPAND_CAT(_BOOL_AND_, EXPAND_CAT(a, EXPAND_CAT(_, b)))
#define _BOOL_AND_FALSE_FALSE FALSE
#define _BOOL_AND_TRUE_FALSE FALSE
#define _BOOL_AND_FALSE_TRUE FALSE
#define _BOOL_AND_TRUE_TRUE TRUE

#define XOR(...) _XOR(__VA_ARGS__)
#define _XOR(a, b) EXPAND_CAT(_BOOL_XOR_, EXPAND_CAT(a, EXPAND_CAT(_, b)))
#define _BOOL_XOR_FALSE_FALSE FALSE
#define _BOOL_XOR_TRUE_FALSE TRUE
#define _BOOL_XOR_FALSE_TRUE TRUE
#define _BOOL_XOR_TRUE_TRUE FALSE

// Conditionals
// only defined for input TRUE and FALSE

// IF(TRUE)(abc)	-> abc
// IF(FALSE)(abc)	-> [empty]
#define IF(cond) EXPAND_CAT(EXPAND_, cond)

// IF_ELSE(TRUE)(abc)(xyz)	-> abc
// IF_ELSE(FALSE)(abc)(xyz)	-> xyz
#define IF_ELSE(cond) EXPAND_CAT(_IF_ELSE_, cond)
#define _IF_ELSE_TRUE(...) __VA_ARGS__ EXPAND_FALSE
#define _IF_ELSE_FALSE(...) EXPAND_TRUE

// Equality

// expand if the two things are equal, only works if there is an ENABLE_EQ_*_* defined
#define EQ(a, b) IF_ELSE(IS_THING(EXPAND_CAT(ENABLE_EQ_, EXPAND_CAT(a, EXPAND_CAT(_, a))))) \
					(TO_STRING(You must define ENABLE_EQ_##a##_##a to use EQ on a)) \
					(NOT(IS_THING(EXPAND_CAT(ENABLE_EQ_, EXPAND_CAT(a, EXPAND_CAT(_, b))))))

// not equal
#define NE(a, b) NOT(EQ(a, b))

// enable equality check for various common values, you can add more elsewhere
#define ENABLE_EQ_TRUE_TRUE
#define ENABLE_EQ_FALSE_FALSE
#define ENABLE_EQ_void_void
#define ENABLE_EQ__

// Get Info

// IS_THING(one_or_more, args)	-> TRUE
// IS_THING()					-> FALSE
// NOTE: the final arg can not be the name of a function-like macro!
// a common way to use is to make two macros (ex. EXAMPLE_TRUE and EXAMPLE_FALSE) and concat your prefix with the
// result of this macro, so you can do different things depending on the thingyness
// the last argument must not be a function-like macro
// depends on: EXPAND_CALL, EXPAND_CAT, EXPAND
// I realize how much of a clusterfuck this is. If you can make it cleaner without failing any tests, plz submit PR
#define IS_THING(...) _IS_THING_A(EXPAND_CAT(_, EXPAND(_IS_THING_D REMOVE_COMMAS(__VA_ARGS__))))
#define _IS_THING_A(a) EXPAND_CALL(_IS_THING_C, _IS_THING_B a (), TRUE)
#define _IS_THING_B() dummy, FALSE
#define _IS_THING_C(a, b, ...) b
#define _IS_THING_D(...) dummy
#define __IS_THING_D

// checks if the argument(s) are completely surrounded by parenthesis
// HAS_PEREN() -> FALSE
// HAS_PEREN("a") -> FALSE
// HAS_PEREN(6, "a") -> FALSE
// HAS_PEREN((), a, 6, "a") -> FALSE
// HAS_PEREN(()) -> TRUE
// HAS_PEREN((a, 6, "a")) -> TRUE
// depends on: EXPAND_CAT, EXPAND
#define HAS_PEREN(...) _HAS_PEREN_C(EXPAND(_HAS_PEREN_A __VA_ARGS__))
#define _HAS_PEREN_A(...) _HAS_PEREN_B
#define _OTHER_HAS_PEREN_A _NO_PEREN(
#define _OTHER_HAS_PEREN_B _YES_PEREN(
#define _HAS_PEREN_C(...) EXPAND_CAT(_OTHER, __VA_ARGS__) )
#define _NO_PEREN(...) FALSE
#define _YES_PEREN(...) NOT(IS_THING(__VA_ARGS__))

// expands to the number of arguments; empty arguments are counted; zero arguments is handeled correctly
// the last argument must not be a function-like macro
// expands to the number of arguments; empty arguments are counted; zero arguments is handled correctly
// depends on: EXPAND_CAT, EXPAND_CALL, IS_THING, _GEN_COUNT, _GEN_COUNT_NUMBERS
#define COUNT(...) IF_ELSE(IS_THING(__VA_ARGS__)) \
						(EXPAND_CALL(_GEN_COUNT, __VA_ARGS__, _GEN_COUNT_NUMBERS)) \
						(0)

/*
// GET_ITEM(abc, FIRST) -> abc
// GET_ITEM(abc, SECOND) -> [empty]
// GET_ITEM((abc, xyz), FIRST) -> abc
// GET_ITEM((abc, xyz), SECOND) -> xyz
// specalized to be used with REPEAT and MAP, may be more generalized later
#define GET_ITEM(func, item) EXPAND_CAT(_GET_ITEM_, HAS_PEREN(func)) (func, item)
#define _GET_ITEM_TRUE(func, item) _GET_ITEM_TRUE_##item func
#define _GET_ITEM_TRUE_FIRST(macro, joiner) macro
#define _GET_ITEM_TRUE_SECOND(macro, joiner) joiner
#define _GET_ITEM_FALSE(func, item) _GET_ITEM_FALSE_##item (func)
#define _GET_ITEM_FALSE_FIRST(func) func
#define _GET_ITEM_FALSE_SECOND(func)
*/

// Many Items

#define REPEAT(func, count) _GEN_REPEAT_##count(func, ORDER_FORWARD)
#define REPEAT_DOWN(func, count) _GEN_REPEAT_##count(func, ORDER_BACKWARD)

// applies the given macro to all additional arguments
// macro should accept item and index
// MAP_DOWN: indexes count down to 0 instead of up from 0
// MAP_REVERSE: items are in reverse order
// MAP_REVERSE_DOWN: both
// depends on: EXPAND_CAT, COUNT, INC_.. (auto generated), DEC_.. (auto generated)
#define MAP(func, ...) EXPAND_CAT(_GEN_MAP_, COUNT(__VA_ARGS__))(func, ORDER_FORWARD, 0, INC_, __VA_ARGS__)
#define MAP_DOWN(func, ...) EXPAND_CAT(_GEN_MAP_, COUNT(__VA_ARGS__))(func, ORDER_FORWARD, EXPAND_CAT(DEC_, COUNT(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE(func, ...) EXPAND_CAT(_GEN_MAP_, COUNT(__VA_ARGS__))(func, ORDER_BACKWARD, EXPAND_CAT(DEC_, COUNT(__VA_ARGS__)), DEC_, __VA_ARGS__)
#define MAP_REVERSE_DOWN(func, ...) EXPAND_CAT(_GEN_MAP_, COUNT(__VA_ARGS__))(func, ORDER_BACKWARD, 0, INC_, __VA_ARGS__)

// Tests

// tests if the input expression matches the expected value and prints result
// depends on:  none
#define TEST_CASE(expr, expected) _TEST_CASE_A(#expr, expr, expected)

// like TEST_CASE, but for when you are testing a macro expression
// depends on:  EXPAND_CALL, TO_STRING
#define TEST_CASE_MACRO(macro_expr, ...) _TEST_CASE_A(#macro_expr, EXPAND_CALL(TO_STRING, macro_expr), #__VA_ARGS__)

#define _TEST_CASE_A(expr_str, result, expected) { \
	const bool success = (result == expected); \
	std::cout << (success ? " .  " : " X  ") << expr_str << ": " << result; \
	if (!success) { \
		std::cout << " (" << expected << " expected)"; \
	} \
	std::cout << std::endl; \
}

#endif // EVIL
