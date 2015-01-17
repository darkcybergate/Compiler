all : bison.tab.c bison.tab.h lex.yy.c parser
bison.tab.c bison.tab.h: bison.y
	bison -v -d -Wconflicts-sr bison.y

lex.yy.c: flex.l bison.tab.h
	flex flex.l

parser: lex.yy.c bison.tab.c bison.tab.h
	g++ bison.tab.c lex.yy.c -lfl -o parser

clean :
	rm bison.tab.*
	rm parser
	rm lex.yy.c
