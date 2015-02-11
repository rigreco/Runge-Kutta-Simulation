/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2vline.c
Description  : G2 Library Routine

               for ProDOS 8 Sys Programs
               Uses Page 2 Double Hi-Res to avoid
               ProDOS Sys Program Load Address at 0x2000

               Double Hi-Res 140 x 192 x 16 color
               vertical line drawing routine.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <dhrpixel.h>

extern struct dhrpixel dhrx;

extern unsigned HB[];

int d2vline(x,y1,y2,drawcolor)
int x, y1, y2, drawcolor;
{
    int y;
    unsigned char *pmain,auxbuf[1];
    unsigned int dest;

    /* swap co-ordinates if out of order */
    if (y2 < y1) {
	   y  = y2;
	   y2 = y1;
	   y1 = y;
	}

    /* plotting is not supported outside viewing window */
    if (x < 0 || x > 139 || y1 < 0 || y2 > 191)return 0;

    /* initialize plotting values */
    dhrcalc(x, drawcolor);

    /* plot a vertical line in the color selected */
    y = y1;
    y2++;
    while (y< y2) {
        /* run the yterm for each pixel */
        /* erase old color then slide new color into place */

		/* auxiliary memory */
		if (dhrx.pattern != 2 && dhrx.pattern != 6) {
			dest = HB[y] + dhrx.xaux;
			auxtomain(dest,dest,&auxbuf[0]);
			auxbuf[0] = (auxbuf[0] & dhrx.mska) | dhrx.caux;
			maintoaux(&auxbuf[0],&auxbuf[0],dest);
		}

		/* main memory */
		if (dhrx.pattern != 0 && dhrx.pattern != 4) {
			pmain = (unsigned char *) (HB[y] + dhrx.xmain);
			*pmain = (*pmain & dhrx.mskm) | dhrx.cmain;
		}
		y++;
	}


return 0;

}
