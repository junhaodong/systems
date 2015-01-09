all: compile

clean:
	rm -f client server *.o

compile: client.c server.c
	gcc -o client client.c
	gcc -o server server.c
