scratchpad: scratchpad.cpp
	g++ -std=c++11 -o scratch_bin scratchpad.cpp

test: test.cpp
	g++ -std=c++11 -o test_bin test.cpp

dump: test.cpp
	g++ -std=c++11 -E test.cpp
