/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dmonplot.c
Description  : G2 Library Routine
               Double Hi-Res 560 x 192 x monochrome plot routine
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned DHRB[];
extern unsigned char dhbmono[];
extern unsigned char dhwmono[];

int dhmonoplot(x,y1,y2,drawcolor)
int x, y1, y2, drawcolor;
{
    int y, xoff, pixel, aux = 1;
    unsigned char *ptr;

#asm
    sta  $c054 ; MAIN MEM
#endasm

    /* swap coordinates if out of order */
    if (y1 > y2) {
		y = y1;
		y1 = y2;
		y2 = y;
	}

	/* allow bi-directional scanline wrap */
	if (x < 0) x+= 560;
	if (x > 559) x-=560;

    if (x < 0 || x > 559 || y1 < 0 || y2 > 191)return 0;

    pixel = (x%14);
    if (pixel > 6) {
		pixel -= 7;
	}
	else {
		#asm
			sta  $c055 ; AUX MEM
		#endasm
	}
    xoff = x/14;

   	y2++;
   	for (y = y1; y < y2; y++) {

		ptr = (unsigned char *) (DHRB[y] + xoff);

		if (drawcolor != 0) {
			/* white */
			*ptr = *ptr | dhwmono[pixel]; /* inclusive OR */
		}
		else {
			/* black */
			*ptr = *ptr & dhbmono[pixel]; /* bitwise AND */
		}
	}

/* reset to main memory */
#asm
    sta  $c054 ; MAIN MEM
#endasm


return 0;

}
