COMP_FLAGS = -lm -ansi -Wall -g
LINK_FLAGS = -lm -g
SOURCE = ../inputs/input11.pja
TARGET = ../outputs/out.c

all: main soft-clean

main: insert.o show.o free.o utils.o check.o symtab.o types.o duplicate.o translate.o builtins.o
	lex pjava.l
	yacc -d pjava.y -v
	cc -o pjava y.tab.c lex.yy.c insert.o show.o free.o utils.o check.o symtab.o types.o duplicate.o translate.o builtins.o -ll -ly ${LINK_FLAGS}

builtins.o: builtins.c
	cc -c -o builtins.o builtins.c ${COMP_FLAGS}

insert.o: insert.c
	cc -c -o insert.o insert.c ${COMP_FLAGS}

show.o: show.c
	cc -c -o show.o show.c ${COMP_FLAGS}

free.o: free.c
	cc -c -o free.o free.c ${COMP_FLAGS}

utils.o: utils.c
	cc -c -o utils.o utils.c ${COMP_FLAGS}

check.o: check.c
	cc -c -o check.o check.c ${COMP_FLAGS}

symtab.o: symtab.c
	cc -c -o symtab.o symtab.c ${COMP_FLAGS}

types.o: types.c
	cc -c -o types.o types.c ${COMP_FLAGS}

duplicate.o: duplicate.c
	cc -c -o duplicate.o duplicate.c ${COMP_FLAGS}

translate.o: translate.c
	cc -c -o translate.o translate.c ${COMP_FLAGS}

soft-clean:
	rm -f *.o ~*

clean: soft-clean
	rm -f lex.yy.c y.tab.c y.tab.h y.output pjava

test:
	./pjava < $(SOURCE) > $(TARGET)
	gcc $(TARGET) -I./ -Wall -g -o ../outputs/out

