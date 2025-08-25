parser: parser.o lexer.o
	gcc parser.o lexer.o -o parser

parser.o: parser.c tokeni.h
	gcc -c parser.c -o parser.o

lexer.o: lex.yy.c
	gcc -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l tokeni.h
	flex lexer.l

.PHONY: clean

clean:
	rm *.yy.* *.o parser