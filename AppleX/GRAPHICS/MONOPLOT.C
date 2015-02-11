/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : monoplot.c
Description  : G2 Library Routine
               Hi-Res 280 x 192 x monochrome plot routine
Written by   : Bill Buckels
Date Written : February 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned HB[];
extern unsigned char dhbmono[];
extern unsigned char dhwmono[];

int monoplot(x,y1,y2,drawcolor)
int x, y1, y2, drawcolor;
{
    int y, xoff, pixel;
    unsigned char *ptr;

    /* swap coordinates if out of order */
    if (y1 > y2) {
		y = y1;
		y1 = y2;
		y2 = y;
	}

	/* allow bi-directional scanline wrap */
	if (x < 0) x+= 280;
	if (x > 279) x-=280;

    if (x < 0 || x > 279 || y1 < 0 || y2 > 191)return 0;

    pixel = (x%7);
    xoff = x/7;

   	y2++;
   	for (y = y1; y < y2; y++) {

		ptr = (unsigned char *) (HB[y] + xoff);

		if (drawcolor != 0) {
			/* white */
			*ptr = *ptr | dhwmono[pixel]; /* inclusive OR */
		}
		else {
			/* black */
			*ptr = *ptr & dhbmono[pixel]; /* bitwise AND */
		}
	}

return 0;

}
