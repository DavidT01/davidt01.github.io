parser: parser.o lexer.o polinom.o
	g++ -std=c++11 parser.o lexer.o polinom.o -o parser

parser.o: parser.tab.cpp parser.tab.hpp
	g++ -std=c++11 -c parser.tab.cpp -o parser.o

lexer.o: lex.yy.c
	g++ -std=c++11 -c lex.yy.c -o lexer.o

polinom.o: polinom.cpp polinom.hpp
	g++ -std=c++11 -c polinom.cpp -o polinom.o

lex.yy.c: lexer.l parser.tab.hpp
	flex lexer.l

parser.tab.cpp parser.tab.hpp: parser.ypp
	bison -d -v parser.ypp

.PHONY: clean

clean:
	rm -rf *.tab.* *.yy.* *.o* parser