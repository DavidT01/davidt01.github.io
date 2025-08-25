parser: lexer.o parser.o logika.o
	g++ -std=c++11 lexer.o parser.o logika.o -o parser

logika.o: logika.cpp logika.hpp
	g++ -std=c++11 -c logika.cpp -o logika.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l 

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp