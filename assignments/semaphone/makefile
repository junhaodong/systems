all: clean compile

clean:
	rm -f control write *.o

compile: control.c write.c
	gcc -o control control.c
	gcc -o write write.c
