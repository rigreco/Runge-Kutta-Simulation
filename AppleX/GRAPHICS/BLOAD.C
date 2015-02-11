/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : bload.c
Description  : G2 Library Routine
               For Hi-Res Mode

Written by   : Bill Buckels
Creation Date: June 6, 1991
Revised      : January 2013

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <fcntl.h>

extern unsigned HB[];

int bload(name)
char *name;
{
   int fh, c=-1;
   if ((fh = open(name,O_RDONLY,0xc3))!=-1) {
   		c = read(fh,(char *)HB[0],0x2000);
   		close(fh);
   		if (c > 8183 && c < 8193) c = 0;
   		else c = -2;
	}
	return c;
}

