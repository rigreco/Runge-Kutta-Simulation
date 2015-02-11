/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : crt80.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Jan 1, 2010

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


crt80()
  {
#asm
  clc
  jsr $c300
#endasm
}