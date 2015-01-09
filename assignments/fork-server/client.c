#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define LINE_LEN 512


int to_server; // well-known pipe
int from_server; // private pipe
char data_from[LINE_LEN]; // from server


int handshake(){
  char pname[LINE_LEN];
	
  // Create private pipe whose name is getpid()
  sprintf(pname, "%d", getpid());
  mkfifo(pname, 0644);
		
	// Attempt to connect and send private pname to server
  to_server = open("wkp", O_WRONLY);
	if (to_server < 0){
		printf("Server is not running. Exiting.\n");
		remove(pname);
		exit(EXIT_FAILURE);
	}
	write(to_server, pname, LINE_LEN);

	// Wait for server response
	from_server = open(pname, O_RDONLY);
  read(from_server, data_from, LINE_LEN);
  printf("<server> %s\n", data_from);
  remove(pname);
}

int main(){
  char data_to[LINE_LEN]; // to server
	handshake();
	while (strcmp(data_to, "exit")){
		printf("\nSend a message to rot13: (\"exit\" to exit)\n");
		fgets(data_to, LINE_LEN, stdin);
		strchr(data_to, '\n')[0] = '\0';
		write(to_server, data_to, strlen(data_to)+1);
		read(from_server, data_from, LINE_LEN);
		printf("<server> %s\n", data_from);
  }
  close(to_server);
  close(from_server);
  return 0;
}

