#ifndef SBBOT_H_INCLUDED
	#define SBOT_H_INCLUDED
	extern void usage(void);
	extern int command(const int, const char*, ...);
	extern int parse(const int, const void*);
#endif
#ifndef SZ_BUFFER
	#define SZ_BUFFER 1024
#endif
