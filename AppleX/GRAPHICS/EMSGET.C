/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : emsget.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 20, 2008

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* copies a chunk of library data from auxmem
   to a buffer */

emsget(emsarraybase,buffer,len)
unsigned emsarraybase;
char *buffer;
int len;
{

   /* the ems buffer starts above the 2nd page of text screen */
   /* in auxiliary memory */

   unsigned hitemp=emsarraybase+0x0C00;

   auxtomain(hitemp,hitemp+len-1,&buffer[0]);
}
