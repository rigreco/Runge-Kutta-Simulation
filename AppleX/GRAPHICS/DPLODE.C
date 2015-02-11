/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dplode.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color Image Loader
               for dhx and dhr images.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <fcntl.h>

extern unsigned DHRB[];

#define BLOCK_SIZE 1280

int dplode(name)
char *name;
{
   unsigned int target;
   int fh,x,x1=0,x2=0,xcnt,y1=0,offset=0,bytes=0,bank=0;
   unsigned char *ptra,*ptrm,ch,buf[BLOCK_SIZE],mainbuf[40],auxbuf[40];

#asm
    sta  $c054 ; MAIN MEM
#endasm

   fh = open(name,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) return -1;

   x = read(fh,buf,5);
   if (x!= 5) {
	   close(fh);
	   return -1;
   }

   if (buf[0] == 'D' && buf[1] == 'H' && buf[3] == 80 && buf[4] == 192 && (buf[2] == 'R' || buf[2] == 'X')) {
	   ch = buf[2];
   }
   else {
 	   close(fh);
	   return -2;
   }

   /* raster oriented raw data */
   if (ch == 'R') {
	   /* read 12 blocks of 16 scanlines */
	   for (x = 0; x < 12; x++) {
		   if (read(fh,buf,BLOCK_SIZE) < BLOCK_SIZE) {
				close(fh);
				return -3;
		   }
		   /* display */
		   for (x1 = 0, x2=40; x1 < BLOCK_SIZE; x1+=80,x2+=80) {

			    /* read the keyboard buffer */
			    /* stop if keypress */
			    ptra = (unsigned char*)0xC000;
			    if (ptra[0] > 127) {
				  x = 12;
				  break;
			    }

				ptra = (unsigned char *)&buf[x1];
				ptrm = (unsigned char *)&buf[x2];
				target = DHRB[y1];
				#asm
					sta  $c055 ; AUX MEM
				#endasm
				movmem(ptra,target,40);
				#asm
					sta  $c054 ; MAIN MEM
				#endasm
				movmem(ptrm,target,40);
				y1++;
		   }
	   }
	   close(fh);
	   return 0; /* done and outa' here */
	}


	if (read(fh,buf,BLOCK_SIZE) < BLOCK_SIZE) {
	   close(fh);
	   return -3;
	}

    /* raster oriented run-length encoded raw data */
    target = DHRB[0];

	do{

	    ch = buf[bytes]; bytes++;
	    if (bytes == BLOCK_SIZE) {
			read(fh,buf,BLOCK_SIZE);
			bytes = 0;
		}

	    /* check to see if its raw */
	    /* if its not, run encoded */
	    if(0xC0 == (ch & 0xc0)){
	       	xcnt = 0x3f & ch;
			ch = buf[bytes]; bytes++;
			if (bytes == BLOCK_SIZE) {
				read(fh,buf,BLOCK_SIZE);
				bytes = 0;
			}
	    }
	    else
	      xcnt = 1;

	 	for(x=0;x<xcnt;x++){
			if (offset < 15360) {

				/* bank 0 - aux mem
				   bank 1 - main mem */
				if (bank == 0) {
				   auxbuf[x2] = ch;
				   bank = 1;
			    }
			    else {
				   mainbuf[x2] = ch;
				   x2++;
				   bank = 0;
			    }

				x1++;

				/* move down one raster every 80 bytes */
				if (x1 >= 80) {
					#asm
						sta  $c055 ; AUX MEM
					#endasm
					movmem(auxbuf,target,40);
					#asm
						sta  $c054 ; MAIN MEM
					#endasm
					movmem(mainbuf,target,40);
					x1 = x2 = bank = 0;
					y1++;
					if (y1 >= 192)break;
					target = DHRB[y1];

				    /* read the keyboard buffer */
				    /* stop if keypress */
				    ptra = (unsigned char*)0xC000;
				    if (ptra[0] > 127) {
					  y1 = 192;
					  offset = 15360;
					  break;
				    }

				}
			}
			else break;

			offset++;
		}
		if (y1 >= 192)break;

     } while(offset<15360);

   close(fh);

   return 0;
}
