tests: tests.cpp define_EVIL.h autogen
	g++ -std=c++11 -o tests_bin tests.cpp

dump: tests.cpp define_EVIL.h autogen
	g++ -std=c++11 -E tests.cpp

autogen: autogen.sh
	./autogen.sh > autogen.h
