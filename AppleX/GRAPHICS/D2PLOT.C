/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2plot.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color plot routine

               for ProDOS 8 Sys Programs
               Uses Page 2 Double Hi-Res to avoid
               ProDOS Sys Program Load Address at 0x2000


Written by   : Bill Buckels
Date Written : February 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <dhrpixel.h>

extern struct dhrpixel dhrx;

extern unsigned HB[]; /* page 2 scanline origins */

int d2plot(x,y,drawcolor)
int x, y, drawcolor;
{
     unsigned char *pmain, auxbuf[1];
     unsigned int dest;

    /* bi-directional wrap supported for one scanline only
       for vector line drawing */
    if (x < 0) x+= 140;
    if (x > 139) x-=140;

    /* other than that... */
    /* plotting is not supported outside viewing window */
    if (x < 0 || x > 139 || y < 0 || y > 191)return 0;

    /* initialize plotting values */
    dhrcalc(x, drawcolor);

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

return 0;

}
