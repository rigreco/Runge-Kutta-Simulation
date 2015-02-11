/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dhrcalc2.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color
               helper routine for pixel drawing functions.

			   inputs: x co-ordinate 0-139 and color 0-15

			   outputs required information for pixel drawing
			   to static structure used by pixel drawing functions.

			   range checking and things of that nature
			   are done outside of here.

			   values that are not used by drawing function logic
			   are not set. said logic depends on the particular
			   bank position in the framebuffer and whether or not
			   that position is using main and/or auxiliary memory.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <dhrpixel.h>

extern struct dhrpixel dhrx;
extern unsigned char dhrbytes[16][4];

dhrcalc2(x, drawcolor)
int x, drawcolor;
{

    dhrx.pattern = (x%7);               /* 7 pixel color pattern */

    /* default - set the initial offset into the framebuffer for each byte pair in
       both memory banks to the first byte to avoid excessive mult and div
       instructions bulking-up this object module with repetitive code */

    dhrx.xaux = dhrx.xmain = (x/7) * 2; /* assign offset for pointer addresses */


    /* Summary of 	AND and OR bitwise operators
	bit a	bit b	a & b	a | b
	0 		0 		0 		0
	0 		1 		0 		1
	1 		0 		0 		1
	1 		1 		1 		1

	Bitmasking can be a confusing business in practice only because
	the code to do so is barely man-readable and even less man-writable...
	but theoretically straight-forward and quite efficient:

	1. 	Bitwise ANDing a binary 1 will preserve the bit and
		Bitwise ANDing a binary 0 will erase the bit.

	2.	Combining 2 values by inclusively ORing them together works
	    fantastically if the areas to be combined have been mutually zeroed
	    in the complementary bits of the other value by using a bitwise AND.
	*/

	/* the following switch statement provides the dhrpixel structure with all the data necessary
	   for the calling function to plot a color in a more or less data-driven abstract manner...
	   review dhrvline to see how the rest of this is done */

    /* extract color bitmap for inclusive OR from 4 - 7 bit bytes x 7 - 4 bit color bitmap patterns
       stored in the dhrbytes array by using a bitwise AND */
    /* provide mask value to erase target framebuffer area before including color bitmap */
    /* increment framebuffer pointer offset to second byte in byte pair if needed */


    switch(dhrx.pattern)
    {
		case 0:
				dhrx.caux  = (dhrbytes[drawcolor][0] & 0x0f); /* 00001111 extract 4 bits */
		        dhrx.mska = 0x70; /* 01110000 erase 4 bits */
				break;
		case 1:
				dhrx.caux  = (dhrbytes[drawcolor][0] & 0x70); /* 01110000 extract 3 bits */
		        dhrx.mska = 0x0f; /* 00001111 erase 3 bits */
 		        dhrx.cmain = (dhrbytes[drawcolor][1] & 0x01); /* 00000001 extract 1 bit */
 		        dhrx.mskm = 0x7e; /* 01111110 erase 1 bit */
 		        break;
		case 2:
				dhrx.cmain = (dhrbytes[drawcolor][1] & 0x1e); /* 00011110 extract 4 bits */
		        dhrx.mskm = 0x61; /* 01100001 erase 4 bits */
		        break;
		case 3:
				dhrx.cmain = (dhrbytes[drawcolor][1] & 0x60); /* 01100000 extract 2 bits */
				dhrx.mskm = 0x1f; /* 00011111 erase 2 bits */

				/* the byte pair splits here at meridian pixel 3 of 7 with the first
				   half of the pixel in the high nibble of the first pair in the main memory bank
				   and the second half of the pixel in the low nibble of the second pair in
				   the auxiliary memory bank */

				dhrx.xaux++ ; /* second byte in auxiliary memory byte pair */
		        dhrx.caux  = (dhrbytes[drawcolor][2] & 0x03); /* 00000011 extract 2 bits */
		        dhrx.mska = 0x7c; /* 01111100 erase 2 bits */
		        break;
		case 4:
				dhrx.xaux++ ; /* second byte in auxiliary memory byte pair */
		        dhrx.caux  = (dhrbytes[drawcolor][2] & 0x3c); /* 00111100 extract 4 bits */
		        dhrx.mska = 0x43; /* 01000011 erase 4 bits */
		        break;
		case 5:
				dhrx.xaux++; /* second byte in auxiliary memory byte pair */
				dhrx.caux  = (dhrbytes[drawcolor][2] & 0x40); /* 01000000 extract 1 bit */
				dhrx.mska = 0x3f; /* 00111111 erase 1 bit */
 		        dhrx.xmain++; /* second byte in main memory byte pair */
 		        dhrx.cmain = (dhrbytes[drawcolor][3] & 0x07); /* 00000111 extract 3 bits */
 		        dhrx.mskm = 0x78; /* 01111000 erase 3 bits */
 		        break;
		case 6:
				dhrx.xmain++; /* second byte in main memory byte pair */
				dhrx.cmain = (dhrbytes[drawcolor][3] & 0x78); /* 01111000 extract 4 bits */
		        dhrx.mskm = 0x07; /* 00000111 erase 4 bits */

	}

return;

}