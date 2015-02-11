/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dwait.c
Description  : G2 Library Routine
               Wait for a period of seconds or until a key is pressed.
               See comments below.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* The timing loop function for dlode's slideshow feature is
   below these comments but first some words about timing loops... */

/* In the BASUC DHGR SLIDE.SHOW example that came with BEAGLE GRAPHICS a
   single loop construct with a value of 30 loops per second of
   duration was used:

B=0
FOR J = 1 TO TIME(I) * 30
	IF  PEEK ( - 16286) > 127 THEN J = TIME(I) * 44
	IF  PEEK ( - 16287) > 127 THEN J = TIME(I) * 44:B = 1
	IF  PEEK ( - 16384) = 155 THEN  POKE  - 16368,0: &  TEXT : END
NEXT J

When I modified the BEAGLE code to add keyboard navigation for my own
version (which is in pure Applesoft and doesn't use the BEAGLE DHGR
extension module), with all due respect for Mark Simonsen, I
discovered that my extra code shown below didn't affect the timing,
which shouldn't surprise anyone since Applesoft is dogslow.

My code below is commented... I am not a big fan of one-liners or
even applesoft in particular but dlode is fundamentally doing the
same thing as the BASUC version without the paddles when it comes
to its slideshow logic so give it a quick read:

FOR J = 1 TO TIME(I) * 30
	REM PADDLE BUTTONS
	IF  PEEK ( - 16286) > 127 THEN J = TIME(I) * 44
	IF  PEEK ( - 16287) > 127 THEN J = TIME(I) * 44:B = 1
	K = PEEK ( - 16384)
	REM ESCAPE KEY, ANY KEY, LEFT ARROW, UP ARROW
	IF  K = 155 THEN  POKE  - 16368,0: GOTO 700
	IF  K > 127 THEN  POKE  - 16368,0: J = TIME(I) * 44 : REM ANY KEY
	IF  K = 136 THEN B = 1 : REM LEFT ARROW - BACK
	IF  K = 139 THEN B = 1 : REM UP ARROW - BACK
NEXT J

By comparison dlode's timing loop is about 30 times or so faster
than interpreted Applesoft which shouldn't surprise anyone, and
if there is a trick here, it is simply in balancing my double loop
while I check for keypresses and using a large enough number to
accomodate the quicker code in Aztec C.

*/

/* timing loop function for slideshow */
#define XTIME 1024L
#define YTIME 32L

/* duration is (hopefully) in seconds on a stock Apple //e without accelerator */
/* use long integers for timing loop to avoid overflow */
/* folks with faster machines can enter larger timeout values from the
   command line and folks with slower disc drives can enter lower
   timeout values if they need to... if a timing loop was
   good enough for the BEAGLES then who am I to complain. */
wait(duration,xmult,yterm)
int duration;
long xmult,yterm;
{
	long x, y;
	int key = 0;

	x=(xmult*duration)/yterm;

	while (x > 0L) {
		y=yterm;
		while (y > 0L) {
		  y--;
		  key = kbhit();
		  if (key!=0) y = 0L;
		}
		x--;
		if (key!=0) x = 0L;
	}

	/* clear stragglers from the keyboard if any */
	if (key != 0) {
	    clearkey();
		while (kbhit())clearkey();
	}

	return key;
}