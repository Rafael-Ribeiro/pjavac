COMP_FLAGS = -lm -ansi -Wall -g
LINK_FLAGS = -lm -g

all: main soft-clean

main: insert.o show.o free.o
	lex pjava.l
	yacc -d pjava.y -v
	cc -o pjava y.tab.c lex.yy.c insert.o show.o free.o -ll -ly ${LINK_FLAGS}

insert.o: insert.c
	cc -c -o insert.o insert.c ${COMP_FLAGS}

show.o: show.c
	cc -c -o show.o show.c ${COMP_FLAGS}

free.o: free.c
	cc -c -o free.o free.c ${COMP_FLAGS}

soft-clean:
	rm -f *.o ~*

clean: soft-clean
	rm -f lex.yy.c y.tab.c y.tab.h y.output pjava
