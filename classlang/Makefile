all: classlang

classlang.tab.c classlang.tab.h:	classlang.y
	bison -d classlang.y

lex.yy.c: classlang.l classlang.tab.h
	flex classlang.l

classlang: lex.yy.c classlang.tab.c classlang.tab.h
	gcc -o classlang classlang.tab.c lex.yy.c

c clean:
	rm -f classlang classlang.tab.c lex.yy.c classlang.tab.h classlang-output.txt classlang.output

db debug-bison:
	bison -d -v classlang.y

r run:
	./classlang