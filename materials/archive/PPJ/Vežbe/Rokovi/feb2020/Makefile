parser: parser.o lexer.o niska.o
	g++ -std=c++11 parser.o lexer.o niska.o -o parser

niska.o: niska.hpp niska.cpp
	g++ -std=c++11 -c niska.cpp -o niska.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp