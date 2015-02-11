/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : liblode.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 23, 2008

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

/* loads a library file */
int liblode(name,libsize)
char *name;
int libsize;
{
   int fh;
   if(libsize>4000)libsize=4000;
   fh = open(name,O_RDONLY,0xc3);

   if (fh == -1) return 0;
   read(fh,(char *)4192,libsize);
   close(fh);

   return 1;

}

