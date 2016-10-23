all: main_gnu main_clang

main_gnu: main.cc
	g++ main.cc -o main_gnu -std=c++11

main_clang: main.cc
	clang++-3.8 main.cc -o main_clang -std=c++11

clean:
	rm -f main_gnu main_clang
