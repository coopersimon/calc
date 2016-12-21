CXX=clang++

CXXFLAGS= -Iinclude -Itarget -std=c++11 -Wall

all : bin/calc

bin/calc : src/calc.cpp target/tree.o target/token.o target/parse.o
	$(CXX) $(CXXFLAGS) src/calc.cpp target/tree.o target/token.o target/parse.o -o bin/calc

target/tree.o : src/tree.cpp include/tree.hpp
	$(CXX) $(CXXFLAGS) -c src/tree.cpp -o target/tree.o

target/token.o : target/token.yy.cpp
	$(CXX) $(CXXFLAGS) -c target/token.yy.cpp -o target/token.o

target/parse.o : target/parse.tab.cpp
	$(CXX) $(CXXFLAGS) -c target/parse.tab.cpp -o target/parse.o

target/token.yy.cpp : src/token.l include/tree.hpp target/parse.tab.hpp
	flex -o target/token.yy.cpp src/token.l

target/parse.tab.cpp target/parse.tab.hpp : src/parse.y include/tree.hpp
	bison -d src/parse.y -o target/parse.tab.cpp

clean :
	rm target/*
	rm bin/*
