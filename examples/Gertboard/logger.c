#include <stdio.h>
#include <time.h>
#include <unistd.h>

#include <wiringPi.h>
#include <gertboard.h>

int main ()
{
  int x1, x2 ;
  double v1, v2 ;

  printf ("\n") ;
  printf ("Gertboard demo: Simple Logger\n") ;
  printf ("=================================\n") ;

// Always initialise wiringPi. Use wiringPiSys() if you don't need
//	(or want) to run as root

  wiringPiSetupSys () ;

// Initialise the Gertboard analog hardware at pin 100

  if(gertboardAnalogSetup (100))
	  printf ("Run: gpio load spi\n") ;

  printf ("\n") ;
  printf ("| Channel 0 | Channel 1 |\n") ;

  for (;;)
  {

// Read the 2 channels:

    x1 = analogRead (100) ;
    x2 = analogRead (101) ;

// 	time_t tm;
// 	time(&tm);	// log time
	time_t ctm = time(NULL);	// log time
	struct tm *ltime = localtime (&ctm);
	char tbuf[20];
	strftime (tbuf, 20, "%F %T", ltime);

// Convert to a voltage:
    v1 = (double)x1 / 1023.0 * 3.3 ;
    v2 = (double)x2 / 1023.0 * 3.3 ;

// Print

//    printf ("|    %6.3f |    %6.3f |  %s\r", v1, v2, ctime(&tm)) ;
    printf ("%6.3f %6.3f %s\n", v1, v2, tbuf) ;
    fflush (stdout) ;
    sleep (60) ;
  }

  return 0 ;
}

