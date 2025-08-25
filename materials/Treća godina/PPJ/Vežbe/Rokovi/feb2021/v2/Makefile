parser: parser.o lexer.o vektor.o
	g++ -std=c++11 parser.o lexer.o vektor.o -o parser

vektor.o: vektor.cpp vektor.hpp
	g++ -std=c++11 -c vektor.cpp -o vektor.o

parser.o: parser.tab.hpp parser.tab.cpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

lex.yy.c: parser.tab.hpp lexer.l
	flex -l lexer.l

parser.tab.hpp parser.tab.cpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean
clean:
	rm -rf *.o *.yy.* *.tab.* parser *.output