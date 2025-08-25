parser: parser.o lexer.o
	gcc -std=c99 parser.o lexer.o -o parser

parser.o: parser.c tokeni.h
	gcc -std=c99 -c parser.c -o parser.o

lexer.o: lex.yy.c
	gcc -std=c99 -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l tokeni.h
	flex lexer.l

.PHONY: clean

clean:
	rm -rf *.yy.* *.o* parser