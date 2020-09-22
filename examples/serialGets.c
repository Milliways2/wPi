#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#define MAXLINE 20

/*
 * serialOpenB:
 *	Open and initialise the serial port, 
 *  setting canonical mode, ignore CR on input, no timeout
 *********************************************************************************
 */
int serialOpenB (const char *device, const int baud, const int max)
{
	struct termios options ;
	int fd = serialOpen(device, baud);
	// Get and modify current options:
	tcgetattr (fd, &options) ;
	
	options.c_lflag |= ICANON;	// set canonical mode (line by line)
	options.c_iflag |= IGNCR;	// ignore CR on input
	options.c_cc [VMIN] = max-1;	// return if max-1 bytes received
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
	*(buf+m) = '\0';
	return (buf) ;
}
