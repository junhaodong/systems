all: clean compile

clean:
	rm -f dirinfo data.txt *~ *.o

compile: dirinfo.c
	gcc -o dirinfo dirinfo.c
