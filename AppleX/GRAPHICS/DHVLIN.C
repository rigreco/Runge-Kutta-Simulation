/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dhvlin.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color
               vertical line drawing routine

               This routine is also called by dhrfbox and dhrfont.

               Writing vertical lines in double hi-res is as effective
               if not arguably more effective for these two calling functions
               than re-calculating a single pixel write repeatedly.

               In the case of dhrfont, since dhrfbox is used both to
               clear the screen and draw filled boxes, dhrvline is already
               compiled into the program so using dhrvline to do a single
               pixel write or a two pixel write made more sense than
               adding the extra baggage of dhrplot to dhrfont.

               In the case of dhrfbox, using a series of vertical lines
               to "flesh-out" the edges of a filled box can be fairly
               effective depending whether or not the filled box falls
               within the co-ordinates supported by blitting with a
               block of pixels.

               Also keeping in mind that drfbox is used to draw
               horizontal lines, so unless vector graphics beyond box
               primitives are needed it just made the most sense to
               keep the code small by avoiding the extra overhead
               of a single pixel write.

               Really, because of the nature of the double hi-res
               screen, the only difference between dhrplot and dhrvline
               is the yterm in dhrvline. And that is at least part of
               the reason that I have broken the cardinal rule of making
               a vertical line the smallest element in most of this
               double hi-res stuff rather than a single-pixel write.

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
extern unsigned char dhrbytes[16][4];
extern char *dhrmain;
extern char *dhraux;


int dhrvline(x,y1,y2,drawcolor)
int x, y1, y2, drawcolor;
{
    int y;
    unsigned char *paux, *pmain;

#asm
    sta  $c054 ; MAIN MEM
#endasm

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
		y++;
	}


return 0;

}
