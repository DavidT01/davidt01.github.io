parser: parser.o lexer.o stringovi.o
	g++ -std=c++11 parser.o lexer.o stringovi.o -o parser

stringovi.o: stringovi.cpp stringovi.hpp
	g++ -std=c++11 -c stringovi.cpp -o stringovi.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp