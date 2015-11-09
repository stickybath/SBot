#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include "sbot.h"

void usage(void)
{
	puts("Usage: sbot [-n nick] [-c channel (required)] [-h host (required)] [-p port]");
}

int command(const int connection, const char *format, ...)
{
	char *buffer = NULL;
	char *ptr = NULL;
	va_list args;
	
	va_start(args, format); 
	if(!(buffer = malloc(SZ_BUFFER))) {
		//handle malloc error
		return 0;
	}
	vsnprintf(buffer, SZ_BUFFER, format, args);
	va_end(args);
	if(!(ptr = (char*)realloc(buffer, strlen(buffer) + 1))) {
		//handle realloc error
		free(buffer);
		return 0;
	}
	printf("<< %s", ptr);
	write(connection, buffer, strlen(buffer));
	free(ptr);

	return 1;
}

int parse(const int connection, const void* data)
{
	char *line = (char*) data;
	int i = 0;
	
	for(i = 0; i  < SZ_BUFFER; i++) {
		if(line[i] == '\n' || line[i] == '\r') {
			line[i + 1] = '\0';
			break;
		}
	}
	if(!strncmp(line, "PING", 4)) {
		printf("DADADADADADADADAD");
		printf(">>%s", line);
		line[1] = 'O';
		command(connection, "%s", line);
		return 1;
	}
	
	return 0;
}
