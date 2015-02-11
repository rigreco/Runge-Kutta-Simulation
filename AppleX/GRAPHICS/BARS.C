/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : bars.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 6, 2008

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* Copyright Bill Buckels 2008 */

/* the following array is based on blue
   and an even column. subscript 1 must be
   used if the destination is an odd column.

   the reverse holds true for an orange
   block.

   I am dealing only with the blue-orange
   palette for this version.

   since either subscript 0 or 1 will be
   used and the screen is 40 bytes wide
   the array only needs to be 41 bytes.

   black and white are not alternating
   bytes so don't require a preformatted
   block like blue and orange.

   see code below.

   */

unsigned char _bars[41] = {
213,170,213,170,213,170,213,170,213,170,
213,170,213,170,213,170,213,170,213,170,
213,170,213,170,213,170,213,170,213,170,
213,170,213,170,213,170,213,170,213,170,213};

extern unsigned HB[];

hbar(row,col, color,width,height)
int row, col, color, width, height;
{
     int bos=row+height;
     char *ptr;
	 int temp;

     ptr = (char *)&_bars[0];

     switch(color) {
	 	case 3: color = 255; break;
	 	case 2: if (col%2 == 0) ptr = (char *)&_bars[1]; break;
	 	case 1: if (col%2 != 0) ptr = (char *)&_bars[1]; break;
        default: color = 128;

	 }

     while (row < bos) {
		temp=HB[row] + col;
		if (color < 128) movmem(ptr,temp,width);
		else setmem(temp,width,color);
	    row++;

	 }

}