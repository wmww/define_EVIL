#ifndef MACRO_UTILS_H
#define MACRO_UTILS_H

#define TEST_CASE(a, b) { \
	auto result = a; \
	std::cout << (result == b ? " .  " : " X  ") << #a << ": " << result; \
	if (result != b) { \
		std::cout << "(" << b << " expected)"; \
	} \
	std::cout << std::endl; \
}

#endif // MACRO_UTILS_H