all: clean compile run

clean: 
	rm -f rwstruct data.txt *~ *.o

compile: rwstruct.c
	gcc -o rwstruct rwstruct.c

run:
	@echo ""
	@./rwstruct
