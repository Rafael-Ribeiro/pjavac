main:
	lex pjava.l
	yacc -d pjava.y -v
	cc -o pjava y.tab.c lex.yy.c insert.c show.c free.c -ll -ly -lm

clean:
	rm -f lex.yy.c y.tab.c y.tab.h y.output pjava
