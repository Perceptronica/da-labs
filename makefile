all:
	g++ -O2 -lm -fno-stack-limit -std=c++20 -x c++ main.cpp -o main