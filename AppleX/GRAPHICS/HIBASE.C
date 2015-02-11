/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : hibase2.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: March 3, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


/* use hibase2.c instead... this routine was modified from
   the original aztec C library but it is too processor intensive
   for real purposes... a table works best despite the larger
   data segment... see hibase2.c */


/* provides base address for page2 hires scanlines  */
/* does not bother to check whether we are in range */
/* gets the address as quickly as possible          */
/* stays away from processor intensive mul and div  */

gethibase(currentline,currentbase)
int currentline;
int *currentbase;
{
  int ybase=0x4000,z,a;

	if(currentline >63)
	   {
	   if (currentline < 128)
	       {
		ybase+=0x28;
		currentline-=64;
	       }
	   else
	       {
	       ybase+=0x50;
	       currentline-=128;
	       }
	    }

	    z=(currentline>>3);
	    a = (z<<7)|ybase;
	    *currentbase = (currentline - (z<<3))<<10 | a;
}

