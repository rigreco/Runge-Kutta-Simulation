/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : lolode.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: March, 2013

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <fcntl.h>

/* the following loads two non-compressed
   graphics image formats associated with
   lores mode...*/

extern int textbase[24];
unsigned char slobuf[1016];

int slolode(name)
char *name;
{
   int fh, status=-2;
   unsigned y, packet, width, height, bufoff, screenoff;

   fh = open(name,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) return -1;
   packet = read(fh,slobuf,1016);
   close(fh);

   switch(packet) {
   		case 1016:  status = 0;
   		            bufoff = (unsigned) &slobuf[0];
   		            screenoff = (unsigned)textbase[0];
   					movmem(bufoff,screenoff,packet);
   					break;
   		case 802:
   		case 962:
   		   			width = (unsigned)slobuf[0];
   					if (width!=40)break;
					height= (unsigned)slobuf[1];
                    if (packet == 802 && height != 20) break;
                    if (packet == 962 && height != 24) break;

                    status = 0;
                    bufoff = (unsigned) &slobuf[2];
                    for (y = 0; y < height; y++) {
						screenoff = (unsigned)textbase[y];
						movmem(bufoff,screenoff,width);
						bufoff+=width;
					}


   }

   return status;
}



