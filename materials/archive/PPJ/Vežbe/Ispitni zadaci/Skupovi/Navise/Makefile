parser: parser.o lexer.o skup.o
	g++ -std=c++11 parser.o lexer.o skup.o -o parser

skup.o: skup.cpp skup.hpp
	g++ -std=c++11 -c skup.cpp -o skup.o

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