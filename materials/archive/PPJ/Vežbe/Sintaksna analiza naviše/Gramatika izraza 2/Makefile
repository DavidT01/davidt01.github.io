parser: parser.o lexer.o
	gcc parser.o lexer.o -o parser
	
parser.o: parser.tab.c parser.tab.h
	gcc -c parser.tab.c -o parser.o
	
lexer.o: lex.yy.c
	gcc -c lex.yy.c -o lexer.o

lex.yy.c: lexer.l parser.tab.h
	flex lexer.l
	
parser.tab.c parser.tab.h: parser.y
	bison -d -v parser.y
	
.PHONY: clean

clean:
	rm parser *.o* *.tab.* *.yy.*
