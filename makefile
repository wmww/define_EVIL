tests: tests.c define_EVIL.h generated
	gcc -std=c11 -o tests_bin tests.c

dump: tests.c define_EVIL.h generated
	gcc -std=c11 -E tests.c

generated: generator.sh
	./generator.sh > generated_EVIL.h
