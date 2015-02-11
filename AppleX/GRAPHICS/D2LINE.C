/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2line.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color
               Bresenham Algorithm line drawing routine

               for ProDOS 8 Sys Programs
               Uses Page 2 Double Hi-Res to avoid
               ProDOS Sys Program Load Address at 0x2000

Written by   : Bill Buckels
Date Written : February 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
d2line(x1, y1, x2, y2, drawcolor)
int x1, y1, x2, y2, drawcolor;
{

	int dx, dy, sx, sy, err, err2;

	if(x1 < x2) {
		dx = x2 - x1;
		sx = 1;
	}
	else {
		sx = -1;
		dx = x1 - x2;
	}

	if(y1 < y2) {
		sy = 1;
		dy = y2 - y1;
	}
	else {
		sy = -1;
		dy = y1 - y2;
	}

	err = dx-dy;

	for (;;) {
		d2plot(x1,y1,drawcolor);

		if(x1 == x2 && y1 == y2)break;

		err2 = err*2;

		if(err2 > (0-dy)) {
			 err = err - dy;
			 x1 = x1 + sx;
		}

		if(err2 <  dx) {
			 err = err + dx;
			 y1 = y1 + sy;
		}
	}
	return;
}
