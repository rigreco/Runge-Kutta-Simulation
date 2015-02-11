/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2init.c
Description  : G2 Library Routine
               Double Hi-Res Routines

               for ProDOS 8 Sys Programs
               Uses Page 2 Double Hi-Res to avoid
               ProDOS Sys Program Load Address at 0x2000

Written by   : Bill Buckels
Date Written : February 2013
Revision     : 1.0 First Release
Licence      : You may use these routines for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


/*
	CLR80VID = $C00C ;disable 80-column display mode (WR-only)
 	SET80VID = $C00D ;enable 80-column display mode (WR-only)

unsigned char *clr80vid = (unsigned char *)0xc00c;
unsigned char *set80vid = (unsigned char *)0xc00d;

	SET80STORE=$C001 ;80STORE On- enable 80-column memory mapping (WR-only)
	CLR80STORE=$C000 ;80STORE Off- disable 80-column memory mapping (Write)

unsigned char *set80store = (unsigned char *)0xc001;
unsigned char *clr80store = (unsigned char *)0xc000;

*/


d2hireson()
{

	/* page 2 hires */
#asm
    jsr  $c300 ; TURN ON 80-COLUMN MODE
    sta  $c000 ; TURN OFF 80 STORE
    sta  $c050 ; GRAPHICS
    sta  $c055 ; PAGE TWO
    sta  $c052 ; GRAPHICS ONLY, NOT MIXED
    sta  $c057 ; HI-RES
    sta  $c05e ; TURN ON DOUBLE RES
 #endasm

}

d2hiresoff()
{
#asm
    sta  $c051 ; TEXT - HIDE GRAPHICS
    sta  $c05f ; TURN OFF DOUBLE RES
    sta  $c054 ; PAGE ONE
    sta  $c001 ; TURN ON 80 STORE
    jsr  $c300 ; TURN ON 80-COLUMN MODE
#endasm
}