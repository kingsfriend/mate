all: scriptlang

scriptlang.tab.c scriptlang.tab.h:	scriptlang.y
	bison -d scriptlang.y

lex.yy.c scriptlang.l.h : scriptlang.l scriptlang.tab.h
	flex scriptlang.l

scriptlang: lex.yy.c scriptlang.tab.c scriptlang.tab.h
	gcc -o scriptlang scriptlang.tab.c lex.yy.c

c clean:
	rm -f scriptlang scriptlang.tab.c lex.yy.c scriptlang.tab.h scriptlang-output.txt scriptlang.output

db debug-bison:
	bison -d -v scriptlang.y

r run:
	./scriptlang