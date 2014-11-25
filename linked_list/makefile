all: clean compile run

clean:
	rm -f llist *~ *.o

compile: llist.c llist.h 
	gcc -o llist llist.c

run:
	@echo ""
	@./llist
