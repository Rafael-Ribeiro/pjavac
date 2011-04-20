main: insert.o show.o free.o
	lex pjava.l
	yacc -d pjava.y -v
	cc -o pjava y.tab.c lex.yy.c insert.o show.o free.o -ll -ly -lm

insert.o: insert.c
	cc -c -o insert.o insert.c -lm -ansi -Wall

show.o: show.c
	cc -c -o show.o show.c -lm -ansi -Wall

free.o: free.c
	cc -c -o free.o free.c -lm -ansi -Wall

clean:
	rm -f lex.yy.c y.tab.c y.tab.h y.output *.o pjava
