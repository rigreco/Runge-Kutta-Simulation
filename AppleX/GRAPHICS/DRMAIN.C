
/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : drmain.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color mode
               and
               Double Lo-Res Mode
               Global Soft Switches for Main Mem and Aux Mem.
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
/* the following soft switches select between
   upper and lower banks of video memory */

char *dhrmain = (char *)49236;
char *dhraux = (char *)49237;
