/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : raxlode.c
Description  : G2 Library Routine
			   For Hi-Res Mode

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <fcntl.h>

/* read and decode RAG images with pcx run-length ecoding */
/* directly onto screen */
/* these are chunk oriented and do not break on scanlines */
/* but the header provides the width and height so no problem */
/* slightly more efficient to encode these in chunks since
   repeats spanning scanlines encode more efficiently.*/

/* a table containing the starting addresses of
   the 192 scanlines in HIRES PAGE 2 */
extern int HB[];

int raxlode(name,xorg,yorg,packet,readbuf)
char *name;
int xorg,yorg,packet;
unsigned char *readbuf;
{
    unsigned char *crt, *ptr, *raxend, ch;
	int fh, x, x1, xcnt;
    int offset=0,width,height,target;

    fh = open(name,O_RDONLY,0x3C); /* open a binary file */
	if (fh == -1) return -1;

    x = read(fh,readbuf,packet); /* read file preferably in mutiples
                                    of 512 byte blocks */

    /* we don't know how many reads we need to make but to be
	   somewhat careful we check our first read of image data outside
	   the pcx decoder to make sure we read something */

    if (x < 3) {  /* image data must follow width and height */
	   close(fh);
	   return -2;
    }

    ptr = (unsigned char *)&readbuf[0];
    raxend = (unsigned char *)&readbuf[packet];

    width = *ptr++;
    height = *ptr++;

    /* the loader centres partial images on the screen
       if loadpoints are invalid */

    /* special case for compressed fullscreen images first
       always load from top left */
    if (width == 40) xorg = 0;
    if (height == 192) yorg = 0;
    if (width == 40 && height == 160) yorg = 0; /* fullscreen mixed text */

    if (xorg < 0 || (xorg+width) > 39) {
       xorg = 20-(width/2); /* break on even byte boundaries */
       if((xorg%2)!=0)xorg--;
   	}
	if (yorg < 0 || yorg > 191) {
		yorg=96-(height/2);
	}

    target = (width * height);
    width = width + xorg;
    height = height + yorg;
    crt = (unsigned char *)(HB[yorg]+xorg);
    x1 = xorg;

	do{

	    ch=*ptr++;

	    if (ptr >= raxend) {
			read(fh,readbuf,packet);
			ptr = (unsigned char *)&readbuf[0];
		}

	    /* check to see if its raw */
	    /* if its not, run encoded */
	    if(0xC0 == (ch & 0xc0)){
	       xcnt = 0x3f & ch;
	       ch = *ptr++;
		   if (ptr >= raxend) {
				read(fh,readbuf,packet);
				ptr = (unsigned char *)&readbuf[0];
		   }
	    }
	    else
	      xcnt = 1;

	    for(x=0;x<xcnt;x++){
			if (offset < target) {
				*crt++ = ch;
				x1++;
				if (x1 >= width) {
					x1 = xorg;
					yorg++;
					if (yorg >= height)break;
					crt = (unsigned char *)(HB[yorg]+xorg);
				}
			}
			else break;

			offset++;
		}

		if (yorg >= height)break;

     } while(offset<target);
     close(fh);
     return 0;
}
