#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include "sbot.h"

int main(int argc, char *argv[])
{
	char *buffer = NULL;
	char *nick = NULL;
	char *channel = NULL;
	char *host = NULL;
	char *port = NULL;
	int ch;
	int connection;
	struct addrinfo hints, *res;	

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
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	getaddrinfo(host, port, &hints, &res);
	connection = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	if(connection == -1) {
		//handle socket error
		return 1;
	}
	connect(connection, res->ai_addr, res->ai_addrlen);
	printf("Assigning nick: %s\n", nick);
	command(connection, "USER %s 0 0 :%s\r\n", nick, nick);
	command(connection, "NICK %s\r\n", nick);
	if(!(buffer = malloc(SZ_BUFFER))) {
		//handle malloc error
		return 1;
	}
	while(read(connection, buffer, SZ_BUFFER) > 0)
	{
		switch(parse(connection, buffer)) {
			case 1:
				command(connection, "JOIN #%s\r\n", channel);
			default:
				break;
		}
	}
	return 0;
}
