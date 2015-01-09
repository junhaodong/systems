#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#define LINE_LEN 512


int from_client; // well-known pipe
int to_client; // private pipe


// Handles SIGINT. Closes pipes and removes the wkp if it exists.
static void sighandler(int signo){
	if (signo == SIGINT){
		close(from_client);
		close(to_client);
		remove("wkp");
		exit(EXIT_SUCCESS);
	}
}

// Make the process a rot13 function.
void process(char *s){
	while (*s){
		if('a' <= *s && *s <= 'z'){
			*s = ((*s - 'a' + 13) %26 ) + 'a';
		}else if ('A' <= *s && *s <= 'Z') {
			*s =  ((*s - 'A' + 13) %26 ) + 'A';
		}
		s++;
	}
}

// Establish connections to client(s).
void handshake(){
  char data_to[LINE_LEN]; // to client
  char data_from[LINE_LEN]; // from client

	// Create and open wkp
	mkfifo("wkp",0644);
  from_client = open("wkp", O_RDONLY);

  // Get input with downstream pipe name and open the pipe
  read(from_client, data_from, LINE_LEN);
	printf("Connection made with client pid: %s\n", data_from);
  to_client = open(data_from, O_WRONLY);
  
  // Send confirmation message
  strncpy(data_to, "Successful connection", LINE_LEN);
  write(to_client, data_to, LINE_LEN);
  
	if (fork()){
		remove("wkp");
		return;
	}
	while(1){
		read(from_client, data_from, LINE_LEN);
		if (!strcmp(data_from,"exit")){
			strncpy(data_to,
							"Closing server connection and exiting\0",
							LINE_LEN);
			write(to_client, data_to, strlen(data_to)+1);
			close(from_client);
			close(to_client);
			exit(EXIT_SUCCESS);
		}
		else{
			data_from[strlen(data_from)] = '\0';
			strcpy(data_to, "\0");
			process(data_from);
			strcat(data_to, data_from);
			write(to_client, data_to,strlen(data_to)+1);
		}
	}
}

int main(){
	signal(SIGINT, sighandler);
	while(1)
		handshake();
	return 0;
}
