#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <sys/types.h>
//#include <sys/stat.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define MAXLINE 20

int serialOpenB (const char *device, const int baud, const int n)
{
	struct termios options ;
	int fd = serialOpen(device, baud);
	// Get and modify current options:
	tcgetattr (fd, &options) ;
	
	options.c_lflag |= ICANON;	// set canonical mode (line by line)
	options.c_iflag |= IGNCR;	// ignore CR on input
	options.c_cc [VMIN] = n-1;	// return if n-1 bytes received
	options.c_cc [VTIME] = 0;	// no timeout
	
	tcsetattr (fd, TCSANOW | TCSAFLUSH, &options) ;
	
	usleep (10000) ;	// 10mS
	
	return fd ;
}


/* Get a newline-terminated string of finite length.
*********************************************************************************
 */

char * serialGets (char *buf, const int n, const int fd)
{
	int m;
	m = read (fd, buf, n);
	if (m != n) {
//	  printf("1 bytes = %d/%d: ", m, n);
	  *(buf+m) = '\0';
    return 0 ;
}
//  return ((int)x) & 0xFF ;
//	printf("2 bytes = %d/%d: ", m, n);
	return (buf) ;
}

int main ()
{
//  int x1, x2 ;
//  double v1, v2 ;
  char line[MAXLINE] ;
  puts("SerialTest\n");

// Always initialise wiringPi. Use wiringPiSys() if you don't need
//	(or want) to run as root

  wiringPiSetupSys () ;
//  int fd = serialOpen("/dev/ttyAMA0", 9600);
  int fd = serialOpenB("/dev/ttyAMA0", 9600, MAXLINE);
 for(;;) {
//	int c =  serialGetchar(fd);
//	if(c > 0) {
//		printf("<%02x %c>", c, c);
//		putchar(c);
//	}
//	sleep(10);
//	printf("serialDataAvail = %d\n", serialDataAvail (fd));

 // serialGets(line, 10, fd);
 //if((serialDataAvail (fd))>10) {
	 
	serialGets(line, MAXLINE, fd);

  	time_t ctm = time(NULL);	// log time
	struct tm *ltime = localtime (&ctm);
	char tbuf[20];
	strftime (tbuf, 20, "%F %T", ltime);
	puts(tbuf);

	puts(line);
	
//	puts("\n");
//	}
}
  return 0 ;
}

