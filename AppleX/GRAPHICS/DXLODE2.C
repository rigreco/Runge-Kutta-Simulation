/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dxlode2.c (modular version - uses dxline.c)
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color Image Loader.
               Load an xcrunched image to the screen
               in either format.

               The library version (dxlode.c)
               which decodes scanlines "inline"
               works slightly faster at the expense of
               object file size. This version calls
               dxline to decode scanlines, and can be used
               if object size is a concern.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <fcntl.h>

#define BLOCK_SIZE 1120
unsigned char dxreadbuf2[BLOCK_SIZE];

/* load a raw xcrunched dhgr image */
int dxrclode2(name)
char *name;
{
	int fh,x,x1,y=0,i,r;
	unsigned char *ptr,c;

#asm
    sta  $c054 ; MAIN MEM
#endasm

   fh = open(name,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) return -1;

   x = read(fh,dxreadbuf2,5); /* read header */
   if (x!= 5) {
	   close(fh);
	   return -1;
   }

   /* check header */
   if (dxreadbuf2[0] != 'X' || dxreadbuf2[1] != 'R' || dxreadbuf2[2] != 'C' ||
       dxreadbuf2[3] != 140 || dxreadbuf2[4] != 192) {
 	   close(fh);
	   return -2;
   }

   /* read 12 blocks of 16 scanline indices */
   for (i = 0; i < 12; i++) {
	   if (read(fh,dxreadbuf2,BLOCK_SIZE) < BLOCK_SIZE) {
	   		close(fh);
	   		return -3;
	   }
	   /* decode and display */
	   for (x = 0; x < BLOCK_SIZE; x+=70) {

		   /* read the keyboard buffer */
		   /* stop if keypress */
		   ptr = (unsigned char*)0xC000;
		   if (ptr[0] > 127) {
			  i = 12;
			  break;
		   }

	       ptr = (unsigned char *)&dxreadbuf2[x];

		   /* check for lines with only 1 color */
		   r = 1;
		   c = ptr[0];
		   for (x1 = 1; x1 < 70; x1++) {
		   	  if (c != ptr[x1]) {
				  dxdline(y,ptr); /* multiple colors */
		   		  r = 0;
		   		  break;
		   	  }
		   }
		   if (r!=0) dxdblock(y,y,(unsigned int)c); /* only 1 color */
	       y++;
	   }
   }
   close(fh);
   return 0;

}


/* load a pcx run-length encoded xcrunched dhgr image */
int dxcclode2(name)
char *name;
{
   int fh,x,xcnt,x1=0,y1=0,offset=0,bytes=0,r=1;
   unsigned char *ptr, ch, cmp, xbuf[70];

#asm
    sta  $c054 ; MAIN MEM
#endasm

   fh = open(name,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) return -1;

   x = read(fh,dxreadbuf2,5); /* read header */
   if (x!= 5) {
	   close(fh);
	   return -1;
   }

   /* check header */
   if (dxreadbuf2[0] != 'X' || dxreadbuf2[1] != 'C' || dxreadbuf2[2] != 'C' ||
       dxreadbuf2[3] != 140 || dxreadbuf2[4] != 192) {
 	   close(fh);
	   return -2;
   }

   /* we don't know how many reads we need to make but to be somewhat careful
      we check our first read of image data outside the pcx decoder and if successful
      we don't check for read errors again */
   if (read(fh,dxreadbuf2,BLOCK_SIZE) < BLOCK_SIZE) {
	   close(fh);
	   return -3;
   }

	do{

	    ch = dxreadbuf2[bytes]; bytes++;
	    if (bytes == BLOCK_SIZE) {
			read(fh,dxreadbuf2,BLOCK_SIZE);
			bytes = 0;
		}

	    /* check to see if its raw */
	    /* if its not, run encoded */
	    if(0xC0 == (ch & 0xc0)){
	       	xcnt = 0x3f & ch;
			ch = dxreadbuf2[bytes]; bytes++;
			if (bytes == BLOCK_SIZE) {
				read(fh,dxreadbuf2,BLOCK_SIZE);
				bytes = 0;
			}
	    }
	    else
	      xcnt = 1;

	 	for(x=0;x<xcnt;x++){
			if (offset < 13440) {

				/* check for lines with only 1 color */
                if (x1 == 0) {
					xbuf[x1] = cmp = ch;
				}
                else {
					xbuf[x1] = ch;
					if (cmp != ch) r = 0;
				}

 				x1++;

				/* move down one raster every 70 bytes */
				if (x1 >= 70) {

				   /* read the keyboard buffer */
				   /* stop if keypress */
				   ptr = (unsigned char*)0xC000;
				   if (ptr[0] > 127) {
					  y1 = 192;
					  offset = 13440;
					  break;
				   }

					/* decode and display scanline */
		            if (r!=0) {
						dxdblock(y1,y1,(unsigned int)cmp); /* only 1 color */
					}
					else {
						dxdline(y1,xbuf); /* multiple colors */
					}
					x1 = 0;
					y1++;
					if (y1 >= 192)break;
				}
			}
			else break;

			offset++;
		}
		if (y1 >= 192)break;

     } while(offset<13440);

   close(fh);

   return 0;
}
