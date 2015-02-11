/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dlores2.c
Description  : G2 Library Routine
               Double Lo-Res Routines

               These Routines are modified
               from my routines for Ordinary Lo-Res Mode
               which can be found in lores.c.

               Note: These routines do not apply to DHGR mode.


Written by   : Bill Buckels
Date Written : January 2013
Revision     : 2.0 March 28, 2013
Licence      : You may use these routines for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* bank 0 color remapping to bank 1 color */
unsigned char dloauxcolor[16] = {
	0,8,1,9,2,10,3,11,4,12,5,13,6,14,7,15};

#define XREG  0
#define YREG  1
#define COLOREG 0

#asm

	instxt	<zpage.h>

XVAL equ  REGS
YVAL equ  REGS+1
COLOR equ REGS

#endasm

unsigned char *dlobyteregptr = (unsigned char *)0x80;
unsigned char *dloeolptr = (unsigned char *)0x2c;

dloplot(x, y, color)
{
	int w, z = x;

/* Double Lo-Res works the same way 80-column text does:
   columns 0, 2, 4, ...78 are stored in AuxRAM,
   and columns 1, 3, 5, ...79 are stored in MainRAM. */

   x = z / 2;
   w = x * 2;

   if (z==w)  dlobyteregptr[COLOREG] = dloauxcolor[color];
   else dlobyteregptr[COLOREG] = (unsigned char)color;

#asm
  LDA COLOR	; Sets the plotting color to N, 0 <= N <= 15
  JSR $F864
#endasm

   if (z!=w)
  {
#asm
	sta  $c054
#endasm
  }
  else {
#asm
	sta  $c055
#endasm
  }

  /* load parameters into user regs */
  dlobyteregptr[XREG] = x;
  dlobyteregptr[YREG] = y;
  /* make ml call */
#asm
  LDY XVAL	; Lo-Res Plot X (Horizontal) Coordinate (0-39)
  LDA YVAL	; Lo-Res Plot Y (Vertical) Coordinate (0-39)
  JSR $F800
#endasm
}

dlogetcolor(x,y)
{

	int w, z = x;

/* Double Lo-Res works the same way 80-column text does:
   columns 0, 2, 4, ...78 are stored in AuxRAM,
   and columns 1, 3, 5, ...79 are stored in MainRAM. */

   x = z / 2;
   w = x * 2;


   if (z!=w)
  {
#asm
	sta  $c054
#endasm
  }
  else {
#asm
	sta  $c055
#endasm
  }

  /* load parameters into user regs */
  dlobyteregptr[XREG] = x;
  dlobyteregptr[YREG] = y;
  /* make ml call */
#asm
  LDY XVAL	; Lo-Res Plot X (Horizontal) Coordinate (0-39)
  LDA YVAL	; Lo-Res Plot Y (Vertical) Coordinate (0-39)
  JSR $F871	; Result (0-15) in Accumulator
  STA COLOR
#endasm
  /* return accumulator value in user reg */
  return (int)dlobyteregptr[COLOREG];
}

dlohline(y, x1, x2, color)
{
	int x;

	/* swap horizontal co-ordinates if out of order */
	if (x1 > x2) {
	   x = x2;
	   x2 = x1;
	   x1 = x;
	}

	x2++;
	for (x = x1; x < x2; x++) dloplot(x, y, color);

}

dlovline(x, y1, y2, color)
{
	int y, z=x;

	/* swap co-ordinates if out of order */
	if (y1 > y2) {
	   y = y2;
	   y2 = y1;
	   y1 = y;
	}

/* Double Lo-Res works the same way 80-column text does:
   columns 0, 2, 4, ...78 are stored in AuxRAM,
   and columns 1, 3, 5, ...79 are stored in MainRAM. */

   x = z/2;
   y = x * 2;

   if (y==z)  dlobyteregptr[COLOREG] = dloauxcolor[color];
   else dlobyteregptr[COLOREG] = (unsigned char)color;

#asm
  LDA COLOR	; Sets the plotting color to N, 0 <= N <= 15
  JSR $F864
#endasm

   if (y != z) /* odd pixel */
  {
#asm
	sta  $c054
#endasm
  }
  else {
#asm
	sta  $c055
#endasm
  }

  /* load parameters into user regs */
  dlobyteregptr[XREG] = x;
  dlobyteregptr[YREG] = y1;
  /* Bottom Y Coordinate (0-47) */
  /* Store it at V2 Lo-res line end-point */
  dloeolptr[YREG] = y2;
  /* make ml call */
#asm
  LDY XVAL	; X Coordinate (0-39)
  LDA YVAL	; Top Y Coordinate (0-47)
  JSR $F828
#endasm
}


dlobox(x1,y1,x2,y2,color)
{

	int x, y;

	/* swap horizontal co-ordinates if out of order */
	if (x1 > x2) {
	   x = x2;
	   x2 = x1;
	   x1 = x;
	}

	/* swap vertical co-ordinates if out of order */
	if (y1 > y2) {
	   y = y2;
	   y2 = y1;
	   y1 = y;
	}

    y = x2 + 1;

	for (x = x1; x < y; x++) dloplot(x, y1,color);
	y1++;
	y2--;
	dlovline(x1, y1, y2, color);
	dlovline(x2, y1, y2, color);
	y2++;
	for (x = x1; x < y; x++) dloplot(x, y2, color);

/* set back to main memory before returning to caller
   from "hi-level" routine */
#asm
	sta  $c054
#endasm

}
