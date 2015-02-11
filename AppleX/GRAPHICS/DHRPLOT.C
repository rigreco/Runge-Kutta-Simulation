/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dhrplot.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color plot routine
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <dhrpixel.h>

extern struct dhrpixel dhrx;

extern unsigned DHRB[];

int dhrplot(x,y,drawcolor)
int x, y, drawcolor;
{
     unsigned char *paux, *pmain;

#asm
    sta  $c054 ; MAIN MEM
#endasm

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
	switch(dhrx.pattern)
	{

		case 0:
		case 4:
				paux = (unsigned char *) (DHRB[y] + dhrx.xaux);
				#asm
					sta  $c055 ; AUX MEM
				#endasm
				*paux = (*paux & dhrx.mska) | dhrx.caux;
				#asm
					sta  $c054 ; MAIN MEM
				#endasm
				break;

		case 1:
		case 3:
		case 5:

				paux = (unsigned char *) (DHRB[y] + dhrx.xaux);
				pmain = (unsigned char *) (DHRB[y] + dhrx.xmain);
				#asm
					sta  $c055 ; AUX MEM
				#endasm
				*paux = (*paux & dhrx.mska) | dhrx.caux;
				#asm
					sta  $c054 ; MAIN MEM
				#endasm
				*pmain = (*pmain & dhrx.mskm) | dhrx.cmain;
				break;

		case 2:
		case 6:
				pmain = (unsigned char *) (DHRB[y] + dhrx.xmain);
				*pmain = (*pmain & dhrx.mskm) | dhrx.cmain;

	}


return 0;

}