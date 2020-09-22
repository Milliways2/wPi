#include <stdio.h>
#include <time.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define MAXLINE 120
extern int serialOpenB (const char *device, const int baud, const int n);
extern char * serialGets (char *buf, const int n, const int fd);
char * rstrip(char *s) {
//	char *p = s;
//	p += strlen(s) -1;
	char *p = s + strlen(s)-1;
	while((*p == '\n')||(*p == '\n')) {
		p--;
	}
	*p = '\0';
	return s;
}
int main ()
{
//  int x1, x2 ;
//  double v1, v2 ;
	char tbuf[20];
	time_t ctm;
	struct tm *ltime;
	char line[MAXLINE];

	puts("SerialTest\n");

// Always initialise wiringPi. Use wiringPiSys() if you don't need
//	(or want) to run as root
	wiringPiSetupSys () ;
//  int fd = serialOpen("/dev/ttyAMA0", 9600);
	int fd = serialOpenB("/dev/ttyAMA0", 9600, MAXLINE);
	for(;;) {
		serialGets(line, MAXLINE, fd);
		ctm = time(NULL);	// log time
		ltime = localtime (&ctm);
		strftime (tbuf, 20, "%F %T", ltime);
		printf("%s %s\n", rstrip(line), tbuf);
		fflush(stdout);
	}
	return 0 ;
}

