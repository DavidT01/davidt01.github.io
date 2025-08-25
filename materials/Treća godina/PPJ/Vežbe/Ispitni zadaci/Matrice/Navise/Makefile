parser: parser.o lexer.o matrix.o
	g++ -std=c++11 parser.o lexer.o matrix.o -o parser

matrix.o: matrix.cpp matrix.hpp
	g++ -std=c++11 -c matrix.cpp -o matrix.o

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm -rf *.tab.* *.yy.* *.o* parser