/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : poke.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: March 9, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

poke(address,value)
int address;
unsigned char value;
{
  unsigned char *poker=(unsigned char *)address;
  *poker=value;

}
