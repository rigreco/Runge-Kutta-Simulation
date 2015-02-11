/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dlores.c
Description  : G2 Library Routine
               Double Lo-Res and Double Hi-Res Routines
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use these routines for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* The same soft switch that changes normal hi-res into double hi-res
   does the trick for lo-res also. Reading or writing $C05E will
   double the resolution, and $C05F will put it back to normal. You
   also have to be in 80-column mode.

   http://www.txbobsc.com/aal/1987/aal8708.html

*/


mode80()
{
#asm
  jsr $c300 ; TURN ON 80-COLUMN MODE
#endasm
}

dloreson()
{
#asm
    jsr  $c300 ; TURN ON 80-COLUMN MODE
    sta  $c050 ; GRAPHICS
    sta  $c052 ; GRAPHICS ONLY, NOT MIXED
    sta  $c054 ; START IN MAIN MEM
    sta  $c056 ; LO-RES
    sta  $c05e ; DOUBLE
#endasm
}

dhireson()
{
#asm
    jsr  $c300 ; TURN ON 80-COLUMN MODE
    sta  $c050 ; GRAPHICS
    sta  $c052 ; GRAPHICS ONLY, NOT MIXED
    sta  $c054 ; START IN MAIN MEM
    sta  $c057 ; HI-RES
    sta  $c05e ; DOUBLE
#endasm
}


dlomixed()
{
#asm
	sta  $c053 ; MIXED TEXT/GRAPHICS
#endasm
}


dlonotmixed()
{
#asm
	sta  $c052 ; GRAPHICS ONLY, NOT MIXED
#endasm
}


clear1()
{
#asm
    sta  $c054 ; MAIN MEM
	jsr  $f832 ; CLEAR
#endasm
}


clear2()
{
#asm
    sta  $c055 ; AUX MEM
	jsr  $f832 ; CLEAR
#endasm
}

dloresoff()
{
#asm
    sta  $c051 ; TEXT
    sta  $c05f ; SINGLE
    sta  $c054 ; PAGE ONE
#endasm
}


/* some functions to output text directly to the screen
   in mixed mode double lo-res */

/* base addresses for last 4 text lines */
/* of primary text page               */
int dlotextbase[4]={
    0x0650,
    0x06D0,
    0x0750,
    0x07D0};

dloputmain(c, ptr)
char c, *ptr;
{
#asm
    sta  $c054 ; MAIN MEM
#endasm
    ptr[0] = c;

}

dloputaux(c, ptr)
char c, *ptr;
{

#asm
    sta  $c055 ; AUX MEM
#endasm
    ptr[0] = c;
}

dloclear_bottom()
{
	char *crt;
	int row, col;
	char c = 32 + 128;

	for (row = 0; row < 4; row++) {
	  crt = (char *)(dlotextbase[row]);
      for (col = 0; col < 40; col++) {
		  dloputaux(c,crt);
		  dloputmain(c,crt);
	     *crt++;
	  }
    }
#asm
    sta  $c054 ; MAIN MEM
#endasm

}

/* row = 0,0 to 3,79 in split screen mode */
/* I am just going directly to the text screen address */
/* and outputting a raw ascii value */
dloprint_bottom(str,row,col)
char *str;
int row, col;
{
     char *crt;
     char c;
     int x, aux = 1, idx, jdx;

     x = col / 2;
     if (col % 2) aux = 0;

     crt = (char *)(dlotextbase[row]+x);

     idx = 0;
     for (;;) {

	   c = str[idx]; idx++;
	   if (c == 0)break;
	   c+=128;
       if (aux == 1) {
	     aux = 0;
	     dloputaux(c,crt);
	   }
	   else {
		 aux = 1;
		 dloputmain(c,crt);
	     *crt++;
	   }
   }

#asm
    sta  $c054 ; MAIN MEM
#endasm

}
