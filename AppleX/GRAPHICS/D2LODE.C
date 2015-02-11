/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2lode.c
Description  : G2 Library Routine

               for ProDOS 8 Sys Programs
               Uses Page 2 Double Hi-Res to avoid
               ProDOS Sys Program Load Address at 0x2000

               Double Hi-Res 140 x 192 x 16 color Image Loader
               Loads two common non-compressed bsaved graphics
               image formats associated with double hires mode.

Written by   : Bill Buckels
Date Written : February 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <fcntl.h>


/* The convention of calling the second image a .AUX file is
   supported in this loader when loading a 2 part file... the load is
   split in the middle after loading the first half into auxiliary
   memory */

extern unsigned HB[]; /* page 2 scanline origins */

int d2lode(name)
char *name;
{
   int fh, status=-2;
   int c, fa = 0, fl = 8192, jdx, idx;
   char name2[64];

   jdx = 999;
   for (idx = 0; name[idx] != 0; idx++) {
        name2[idx] = name[idx];
		if (name[idx] == '.') jdx = idx;
   }
   name2[idx] = 0;

   if (jdx != 999) name2[jdx] = 0;
   strcat(name2,".AUX");

   fl = 8192;
   fh = open(name2,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) {
	   fl = 16384;
	   fh = open(name,O_RDONLY,0x3C);
	   if (fh == -1)return -1;
   }


   switch(fl) {
	   case 16384:
	   case 8192:
	       /* read to main memory */
	       c = read(fh,(char *)HB[0],8192);
	       if (c != 8192)break;
	       /* move to auxiliary memory */
	       maintoaux(HB[0],HB[0]+8191,HB[0]);

           if (fl == 8192) {
           		close(fh);
           		fh = open(name,O_RDONLY,0x3C); /* open a binary file */
           		if (fh == -1)return -1;

		   }
		   /* read to main memory */
           c = read(fh,(char *)HB[0],8192);
           if (c != 8192)break;
           status=0;
		   break;
   }

   close(fh);

   return status;
}
