/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : lopixel.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Dec 4, 2009

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern int textbase[24];
setlopixel(color,x,y,page)
int color, x, y, page;
{
     unsigned char *crt, c1, c2;
     int y1;


     y1 = y / 2;
     if (page !=0) x = x + 1024;



     c2 = (unsigned char ) (color & 15);


     if (y%2 == 0) {
		 /* even rows in low nibble */
		 /* mask value to preserve high nibble */
		 c1 = 240;
	 }
	 else {
		 /* odd rows in high nibble */
		 /* mask value to preserve low nibble */
		 c1 = 15;
		 c2 = c2 * 16;
	 }

     crt = (unsigned char *)(textbase[y1]+x);
     crt[0] &= c1;
     crt[0] |= c2;

}