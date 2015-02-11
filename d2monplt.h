/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2monplt.h
Description  : G2 Library Routine
               Double Hi-Res 560 x 192 x monochrome plot routine
Written by   : Bill Buckels
Date Written : July 31, 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned HB[]; /* page 2 scanline origins */
extern unsigned char dhbmono[];
extern unsigned char dhwmono[];

int d2monoplot(x,y1,y2,drawcolor)
int x, y1, y2, drawcolor;
{
    int y, xoff, pixel, aux = 0;
    unsigned char *ptr, auxbuf[1];
    unsigned dest;

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
		/* main memory */
		pixel -= 7;
	}
	else {
		/* auxiliary memory */
		aux = 1;
		ptr = (unsigned char *)&auxbuf[0];
	}
    xoff = x/14;

   	y2++;
   	for (y = y1; y < y2; y++) {

        if (aux == 1) {
			/* auxiliary memory */
			dest = HB[y] + xoff;
			auxtomain(dest,dest,&auxbuf[0]);
		}
		else {
			/* main memory */
			ptr = (unsigned char *) (HB[y] + xoff);
		}

		if (drawcolor != 0) {
			/* white */
			*ptr = *ptr | dhwmono[pixel]; /* inclusive OR */
		}
		else {
			/* black */
			*ptr = *ptr & dhbmono[pixel]; /* bitwise AND */
		}
		if (aux == 1) {
			/* auxiliary memory */
			maintoaux(&auxbuf[0],&auxbuf[0],dest);
		}
	}

return 0;

}
