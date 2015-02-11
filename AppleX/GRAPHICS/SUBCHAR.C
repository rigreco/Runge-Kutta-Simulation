/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : subchar.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 4, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* substitute a character in the filechar array with a special */

subchar(num,newchar)
char num;
char *newchar;
{
  char *filechar=(char*)0x0c00;
  int i;
  int j=(num-32)*8;

  for(i=0;i<8;i++)filechar[j+i]=newchar[i];
}

