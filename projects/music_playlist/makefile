files = song.c library.c main.c

all: clean compile run

clean:
	rm -f musicLib *~ *.o

compile:
	gcc -o musicLib $(files)

# @ stops the terminal from printing the commands
run:
	@echo ""
	@./musicLib
