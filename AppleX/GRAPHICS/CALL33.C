/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : call33.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Jan 1, 2010

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

catalog()
{
#asm
	clc
	jsr  $a56e
#endasm
}

reboot()
{
#asm
	clc
	jsr  $faa6
#endasm
}

bell()
{
#asm
	clc
	jsr  $ff3a
#endasm
}

bellerr()
{
#asm
	clc
	jsr  $ff2d
#endasm
}

scr_apple()
{
#asm
	clc
	jsr  $fb60
#endasm
}

loclear()
{
#asm
	clc
	jsr  $f832
#endasm
}

