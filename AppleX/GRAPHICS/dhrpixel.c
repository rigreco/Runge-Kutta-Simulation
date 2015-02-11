/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dhrpixel.c
Description  : G2 Library Routine
               global structure implementation for G2 library required
               by Double Hi-Res 140 x 192 x 16 color plot routines.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <dhrpixel.h>

struct dhrpixel dhrx = {0,0,0,'\x00','\x00','\x00','\x00'};
