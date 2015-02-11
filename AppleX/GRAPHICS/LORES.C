/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : lores.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Dec 4, 2009

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#define XREG  0
#define YREG  1
#define COLOREG 0

#asm

	instxt	<zpage.h>

XVAL equ  REGS
YVAL equ  REGS+1
COLOR equ REGS

#endasm

unsigned char *byteregptr = (unsigned char *)0x80;
unsigned char *eolptr = (unsigned char *)0x2c;

setcolor(value)
{
  /* load parameters into user reg */
  byteregptr[COLOREG] = value;
  /* make ml call */
#asm
  LDA COLOR	; Sets the plotting color to N, 0 <= N <= 15
  JSR $F864
#endasm
}


loplot(x, y)
{
  /* load parameters into user regs */
  byteregptr[XREG] = x;
  byteregptr[YREG] = y;
  /* make ml call */
#asm
  LDY XVAL	; Lo-Res Plot X (Horizontal) Coordinate (0-39)
  LDA YVAL	; Lo-Res Plot Y (Vertical) Coordinate (0-39)
  JSR $F800
#endasm
}


getlocolor(x,y)
{
  /* load parameters into user regs */
  byteregptr[XREG] = x;
  byteregptr[YREG] = y;
  /* make ml call */
#asm
  LDY XVAL	; Lo-Res Plot X (Horizontal) Coordinate (0-39)
  LDA YVAL	; Lo-Res Plot Y (Vertical) Coordinate (0-39)
  JSR $F871	; Result (0-15) in Accumulator
  STA COLOR
#endasm
  /* return accumulator value in user reg */
  return (int)byteregptr[COLOREG];
}


lohlin(y, x1, x2)
{
  /* load parameters into user regs */
  byteregptr[XREG] = x1;
  byteregptr[YREG] = y;
  /* Rightmost X Coordinate (0-39) */
  /* Store it at H2 Lo-res line end-point */
  eolptr[XREG] = x2;
  /* make ml call */
#asm
  LDY XVAL	; Leftmost X Coordinate (0-39)
  LDA YVAL	; Y Coordinate (0-47)
  JSR $F819
#endasm
}

lovlin(x, y1, y2)
{
  /* load parameters into user regs */
  byteregptr[XREG] = x;
  byteregptr[YREG] = y1;
  /* Bottom Y Coordinate (0-47) */
  /* Store it at V2 Lo-res line end-point */
  eolptr[YREG] = y2;
  /* make ml call */
#asm
  LDY XVAL	; X Coordinate (0-39)
  LDA YVAL	; Top Y Coordinate (0-47)
  JSR $F828
#endasm
}


lobox(x1,y1,x2,y2,color)
{
	setcolor(color);
	lohlin(y1, x1, x2);
	y1++;
	y2--;
	lovlin(x1, y1, y2);
	lovlin(x2, y1, y2);
	y2++;
	lohlin(y2, x1, x2);
}
