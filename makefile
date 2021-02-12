tests: tests.cpp define_EVIL.h generated
	g++ -std=c++11 -o tests_bin tests.cpp

dump: tests.cpp define_EVIL.h generated
	g++ -std=c++11 -E tests.cpp

generated: generator.sh
	./generator.sh > generated_EVIL.h
