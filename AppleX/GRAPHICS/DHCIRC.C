/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dhcirc.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color circle routine
               Using Bresenham Algorithm with crude aspect modification
               in the xterm only. 1 x 2 aspect for a circle.
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
dhrcircle(x1, y1, radius, drawcolor, xmult, xdiv)
{
  int f = 1 - radius;
  int ddfx = 1;
  int ddfy = -2 * radius;
  int x = 0;
  int y = radius;
  int xxaspect, xyaspect;

  /* top and bottom */
  dhrplot(x1, y1 + radius, drawcolor);
  dhrplot(x1, y1 - radius, drawcolor);

  /* sides */
  /* a 1 x 2 aspect */
  /* compresses the xterm for a circle */
  if (xmult > 0 && xdiv > xmult) xyaspect = (y * xmult)/xdiv;
  else xyaspect = y;

  dhrplot(x1 + xyaspect, y1, drawcolor);
  dhrplot(x1 - xyaspect, y1, drawcolor);

  while(x < y)
  {
    if(f >= 0)
    {
      y--;
      ddfy += 2;
      f += ddfy;
    }
    x++;
    ddfx += 2;
    f += ddfx;

    if (xmult > 0 && xdiv > xmult) {
		 /* a 1 x 2 aspect */
		 /* compresses the xterm for a circle */
		xxaspect = (x * xmult)/xdiv;
		xyaspect = (y * xmult)/xdiv;
	}
	else {
		xxaspect = x;
		xyaspect = y;
	}

    /* top and bottom */
	dhrplot(x1 + xxaspect, y1 + y, drawcolor); /* bottom right */
	dhrplot(x1 - xxaspect, y1 + y, drawcolor); /* bottom left */

	dhrplot(x1 + xxaspect, y1 - y, drawcolor); /* top right */
	dhrplot(x1 - xxaspect, y1 - y, drawcolor); /* top left */

    /* sides */
	dhrplot(x1 + xyaspect, y1 + x, drawcolor); /* mid bottom right */
	dhrplot(x1 - xyaspect, y1 + x, drawcolor); /* mid bottom left */

	dhrplot(x1 + xyaspect, y1 - x, drawcolor); /* mid top right */
	dhrplot(x1 - xyaspect, y1 - x, drawcolor); /* mid top left */

  }

  return;
}
