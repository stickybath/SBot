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
	unsigned int sz_bff = 1024;
	va_list args;
	
	va_start(args, format); 
	if(!(buffer = malloc(sz_bff))) {
		//handle malloc error
		return 0;
	}
	vsnprintf(buffer, sz_bff, format, args);
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
