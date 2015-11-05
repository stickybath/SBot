#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "sbot.h"

int main(int argc, char *argv[])
{
	char *nick = NULL;
	char *channel = NULL;
	char *host = NULL;
	char *port = NULL;
	
	int ch;
	
	while((ch = getopt(argc, argv, "n:c:h:p:")) !=  EOF) {
		switch(ch) {
		case 'n':
			nick = optarg;
			break;
		case 'c':
			channel = optarg;
			break;
		case 'h':
			host = optarg;
			break;
		case 'p':
			port = optarg;
			break;
		default:
			usage();
			return 0;
		}
	}
	if(!channel) {
		usage();
		return 0;
	}
	if(!host) {
		usage();
		return 0;
	}
	if(!nick) {
		if(!(nick = malloc(5))) {
			//malloc error handling.
			return 1;
		}
		strcat(nick, "sBot");
	}
	if(!port) {
		if(!(port = malloc(5))) {
			//malloc error handling.
			return 1;
		}
		strcat(port, "6667");
	}		
	printf("Connecting to %s:%s as %s.\n", host, port, nick);
	//connect function
	printf("Joining #%s.\n", channel);	

	return 0;
}
