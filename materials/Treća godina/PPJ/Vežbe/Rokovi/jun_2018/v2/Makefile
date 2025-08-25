parser: parser.o lexer.o matrice.o
	g++ -std=c++11 lexer.o parser.o matrice.o -o parser

matrice.o: matrice.cpp matrice.hpp
	g++ -std=c++11 -c matrice.cpp -o matrice.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lex.yy.c: lexer.l parser.tab.hpp
	flex -l lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp