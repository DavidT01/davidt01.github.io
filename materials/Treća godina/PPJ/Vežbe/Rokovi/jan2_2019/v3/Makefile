parser: parser.o lexer.o razlomak.o
	g++ -std=c++11 parser.o lexer.o razlomak.o -o parser

razlomak.o: razlomak.cpp razlomak.hpp
	g++ -std=c++11 -c razlomak.cpp -o razlomak.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp