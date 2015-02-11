/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : putchar.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use these routines for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


#asm

	instxt	<zpage.h>

#endasm


/* print character using cout */
cputchar(ch)
{

  unsigned char *regsptr = (unsigned char *)0x80;

  /* load char into user reg */
  regsptr[0] = ch;

  /* make ml call */
#asm
  LDA REGS
  JSR $FDED ;SEND IT THROUGH THE COUT ROUTINE
#endasm

}

mousetexton()
{

	/* MouseText Characters
       Apple II Technical Notes Developer Technical Support

       http://mirrors.apple2.org.za/apple.cabi.net/FAQs.and.INFO/A2.TECH.NOTES.ETC/A2.CLASSIC.TNTS/mouse006.html

       */

	#asm

	LDA #$1B           ;MOUSETEXT ON
	JSR $FDED

	#endasm

}

mousetextoff()
{
	#asm

	LDA #$18           ;MOUSETEXT OFF
	JSR $FDED

	#endasm
}

reversetext()
{

	#asm

	LDA #$0F           ;REVERSE
	JSR $FDED

	#endasm

}

normaltext()
{
	#asm

	LDA #$0E           ;NORMAL
	JSR $FDED

	#endasm

}