/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : fonlode.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 4, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <stdio.h>
#include <fcntl.h>
#include <prodos.h>
#include <sgtty.h>
#include <device.h>
#include <sysfunc.h>

fontlode()
{
   int fh;
   fh = open("FATFONT.FNT",O_RDONLY,0xc3);
   read(fh,(char *)0x0c00,1096);
   close(fh);
}


