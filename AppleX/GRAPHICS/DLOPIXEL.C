
/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dlopixel.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: March 28, 2013

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


/* double lo-res routine */

setdlopixel(color,x,y)
int color, x, y;
{
    /* wrapper for ml routines */
	/* dlosetcolor(color); */
	dloplot(x, y, color);

/* set back to main memory before returning to caller */

#asm
	sta  $c054
#endasm

}