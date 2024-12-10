all:
	g++ -O2 -lm -fno-stack-limit -std=c++20 -x c++ ../lab2-patricia/solution.cpp -pg -g -o executable
run:
	(./executable < test.in) > test.out
gprof:
	make
	make run
	(gprof executable) > gprof.out
valgrind:
	make
	make run
	valgrind ./executable
clean:
	rm executable test.out gprof.out gmon.out
