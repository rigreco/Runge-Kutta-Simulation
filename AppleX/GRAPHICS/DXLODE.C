/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dxlode.c (inline version - does not use dxline.c)
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color Image Loader.
               Load an xcrunched image to the screen
               in either format.

               Note: See dxlode2.c for the modular version of
               this code. This inline version works slightly
               faster than the modular version but is a little
               larger.

               The code in putrax.c that I wrote afew years back
               might offer an easier read if you just want to look
               at some simpler code that uses ZSoft PCX RLE but be
               forewarned that putrax operates on raw data and does
               not decode bitmapped indices like this code does.

               Nevertheless it is a layer or two of indirection
               simpler... and a guy needs a place to start unless
               he's done some of these before and also knows his
               Apple II graphics and some other stuff that I hope
               will rub-off when he gets what I am doing here.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <fcntl.h>

extern unsigned DHRB[];
extern unsigned char dhrbytes[16][4];
extern unsigned char dhapix[16][7];
extern unsigned char dhmpix[16][7];


/* note: BLOCK_SIZE (see below) has been set to match the read loop for
         non-RLE images... before you change this read the code... and change
         the other define (BLOCKS) accordingly.

         The non-RLE code reads 12 blocks of 16 scanline indices.
         doubling the size of this buffer made very little difference
         in the loading of these images during my testing. I never bothered
         to test a smaller buffer size much because I decided that it was
         acceptable for my purposes to give up 1K or so of memory for
         a read buffer.

         If you do make BLOCK_SIZE larger or smaller stay within even multiples...

         a smaller BLOCK_SIZE of 560 will use 560 bytes less memory but require
         twice as many reads. It will cause this code to read 24 blocks of
         8 scanlines.

         a larger BLOCK_SIZE of 2240 will use 1120 bytes more memory and will
         require half the the reads. It will cause this code to read 6 blocks
         of 32 scanlines.


         */


/* the following 3 defines are constant and must not be changed
   unless you are modifying this code to handle variable size images (image fragments)
   in my format... or modifying this code for other screen modes or for
   something compltely different of course...  */

#define IMAGE_LINES  192
#define IMAGE_LINE   70
/* 192 * 70 = 13440 */
#define IMAGE_SIZE   13440

/* the following 2 defines must be equal multiples of IMAGE_LINE
   and must be equally divisible by image size.
   see notes above and code below */
#define BLOCKS      12
/* BLOCK_SIZE = (IMAGE_SIZE / BLOCKS) */
#define BLOCK_SIZE 1120
/* BLOCK_LINES = (BLOCK_SIZE / IMAGE_LINE) */

unsigned char dxreadbuf[BLOCK_SIZE];

/* load a raw xcrunched dhgr image */
int dxrclode(name)
char *name;
{
	unsigned int target;
	register int x1=0, z, i, j, ci, p;
	int fh,x,y=0,cnt,r;
	unsigned char *ptr,c,ch,mbuf[40],abuf[40];

#asm
    sta  $c054 ; MAIN MEM
#endasm

   fh = open(name,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) return -1;

   x = read(fh,dxreadbuf,5); /* read header */
   if (x!= 5) {
	   close(fh);
	   return -1;
   }

   /* check header */
   if (dxreadbuf[0] != 'X' || dxreadbuf[1] != 'R' || dxreadbuf[2] != 'C' ||
       dxreadbuf[3] != 140 || dxreadbuf[4] != 192) {
 	   close(fh);
	   return -2;
   }

   /* read 12 blocks of 16 scanline indices */
   /* doubling the size of this buffer made very little difference
      in the loading of these images during my testing */
   for (cnt = 0; cnt < BLOCKS; cnt++) {
	   if (read(fh,dxreadbuf,BLOCK_SIZE) < BLOCK_SIZE) {
	   		close(fh);
	   		return -3;
	   }
	   /* decode and display */
	   for (x = 0; x < BLOCK_SIZE; x+=IMAGE_LINE) {

		   /* read the keyboard buffer */
		   /* stop if keypress */
		   ptr = (unsigned char*)0xC000;
		   if (ptr[0] > 127) {
			  cnt = BLOCKS;
			  break;
		   }

	       ptr = (unsigned char *)&dxreadbuf[x];

		   /* check for lines with only 1 color */
		   r = 1;      /* repeat = true */
		   c = ptr[0]; /* store first byte per line */
		   for (x1 = 1; x1 < IMAGE_LINE; x1++) {
		   	  if (c != ptr[x1]) {
				  /* multiple colors */
		   		  r = 0; break; /* repeat = false */
		   	  }
		   }

		   /* multiple colors - repeat = false */
		   if (r==0) {

				/* decode and display scanline */
				/* set buffers to black */
				setmem(abuf,40,0);
				setmem(mbuf,40,0);

				i=0, j=1, ci, p=-1;

				/* decode the scanline indices */
				for (x1 = 0; x1 < IMAGE_LINE; x1++) {
					/* unpack the 2 colors */
					/* map the low nibble first */
					c = ptr[x1];
					ci = (int )(c & 0xf);
					for(z=0;z<2;z++) {
						p++;
						if (z==1)ci = (int )(c >> 4);

						if (ci == 0) {
							/* skip black pixels - buffers are initially black */
							if (p == 6) {
								p= -1;
								i+=2;
								j+=2;
							}
						}
						else {
						switch(p) {
							case 0: abuf[i]  = dhapix[ci][0]; 			/* 00001111 4 bits */
									break;
							case 1: abuf[i] = (abuf[i] | dhapix[ci][1]);/* 01110000 3 bits */
									mbuf[i] =  dhmpix[ci][1]; 			/* 00000001 1 bit  */
									break;
							case 2: mbuf[i] = (mbuf[i] | dhmpix[ci][2]);/* 00011110 4 bits */
									break;
							case 3: mbuf[i] = (mbuf[i] | dhmpix[ci][3]);/* 01100000 2 bits */
									abuf[j] =  dhapix[ci][3]; 			/* 00000011 2 bits */
									break;
							case 4: abuf[j] = (abuf[j] | dhapix[ci][4]);/* 00111100 4 bits */
									break;
							case 5: abuf[j] = (abuf[j] | dhapix[ci][5]);/* 01000000 1 bit  */
									mbuf[j] =  dhmpix[ci][5]; 			/* 00000111 3 bits */;
									break;
							case 6: mbuf[j] = (mbuf[j] | dhmpix[ci][6]);/* 01111000 4 bits */
									p = -1;
									i+=2;
									j+=2;
							}
						}
					}
				}
				target = DHRB[y];
				/* display the scanline */
				#asm
					sta  $c055 ; AUX MEM
				#endasm
				movmem(abuf,target,40);
				#asm
					sta  $c054 ; MAIN MEM
				#endasm
				movmem(mbuf,target,40);
			}
			else {

				/* only 1 color - repeat = true */

				if (c == 0) { /* black */
					setmem(abuf,40,0);
					setmem(mbuf,40,0);
				}
				else {

					ci = (int )(c & 0xf); /* color indices 1-14 */

					if (ci == 15) { /* white */
						setmem(abuf,40,0x7f);
						setmem(mbuf,40,0x7f);

					}
					else {
						/* other colors */
						/* expand byte pairs to build scanline buffers */
						/* interleaf 7 pixels between main and aux memory */
						for (i = 0; i < 40; i++) {
							abuf[i] = dhrbytes[ci][0];
							mbuf[i] = dhrbytes[ci][1];
							i++;
							abuf[i] = dhrbytes[ci][2];
							mbuf[i] = dhrbytes[ci][3];
						}
					}
				}

				/* now write the pixels */
				target = DHRB[y];
				#asm
					sta  $c055 ; AUX MEM
				#endasm
				movmem(abuf,target,40);
				#asm
					sta  $c054 ; MAIN MEM
				#endasm
				movmem(mbuf,target,40);
			}
			/* set to next line */
	        y++;
	   }
   }
   close(fh);
   return 0;

}

/* load a pcx run-length encoded xcrunched dhgr image */
int dxcclode(name)
char *name;
{
   unsigned int target;
   register int x1=0, z, i, j, ci, p;
   int fh,x,xcnt,y1=0,offset=0,bytes=0,r;
   unsigned char *ptr, ch, c, xbuf[IMAGE_LINE], mbuf[40], abuf[40];

#asm
    sta  $c054 ; MAIN MEM
#endasm

   fh = open(name,O_RDONLY,0x3C); /* open a binary file */
   if (fh == -1) return -1;

   x = read(fh,dxreadbuf,5); /* read header */
   if (x!= 5) {
	   close(fh);
	   return -1;
   }

   /* check header */
   if (dxreadbuf[0] != 'X' || dxreadbuf[1] != 'C' || dxreadbuf[2] != 'C' ||
       dxreadbuf[3] != 140 || dxreadbuf[4] != 192) {
 	   close(fh);
	   return -2;
   }

   /* we don't know how many reads we need to make but to be somewhat careful
      we check our first read of image data outside the pcx decoder and if successful
      we don't check for read errors again */
   if (read(fh,dxreadbuf,BLOCK_SIZE) < BLOCK_SIZE) {
	   close(fh);
	   return -3;
   }

	do{

	    ch = dxreadbuf[bytes]; bytes++;
	    if (bytes == BLOCK_SIZE) {
			read(fh,dxreadbuf,BLOCK_SIZE);
			bytes = 0;
		}

	    /* check to see if its raw */
	    /* if its not, run encoded */
	    if(0xC0 == (ch & 0xc0)){
	       	xcnt = 0x3f & ch;
			ch = dxreadbuf[bytes]; bytes++;
			if (bytes == BLOCK_SIZE) {
				read(fh,dxreadbuf,BLOCK_SIZE);
				bytes = 0;
			}
	    }
	    else
	      xcnt = 1;

	 	for(x=0;x<xcnt;x++){
			if (offset < IMAGE_SIZE) {

                /* test for scanlines with one color only */
                if (x1 == 0) {
					r = 1;             /* repeat = true */
					xbuf[x1] = c = ch; /* store first byte per scanline */
				}
				else {
					if (c!=ch) r = 0; /* multiple colors */
					xbuf[x1] = ch;
				}

 				x1++;

				/* move down one raster every 70 bytes */
				if (x1 >= IMAGE_LINE) {

				   /* read the keyboard buffer */
				   /* stop if keypress */
				   ptr = (unsigned char*)0xC000;
				   if (ptr[0] > 127) {
					  y1 = IMAGE_LINES;
					  offset = IMAGE_SIZE;
					  break;
				   }

					/* this version of dxlode has the display code inline (below).
					   it is slightly faster than the modular version
					   but it is also slightly larger since the display code
					   is duplicated for run-lenth encoded images and
					   non-run-length encoded images.

					   this version is also one heck of a lot harder to
					   read than the modular version and I should add, it was
					   harder to write since I needed to write several
					   inline versions to create the modular version, and
					   then used the modular version to create the inline
					   version.

					   I also messed with encoding image data directly before
					   encoding pixel-level indices after being completely
					   disgusted with the poor compression that raw data yielded
					   despite much quicker load times.

					   Raw data has its place however... see the comments
					   in my xpack utility for a place to start for
					   my raw data compression version which is complimented
					   by the loader code in the G2 library routine dplode.c
					   and the dplode command line loader for the Aztec C Shell
					   in the Applex\projects\dhr\shell directory.


					   */

                    /* multiple colors - repeat = false */
                    if (r == 0) {

						/* decode and display scanline */
						/* set buffers to black */
						setmem(abuf,40,0);
						setmem(mbuf,40,0);

						i=0, j=1, ci, p=-1;

						/* decode the scanline indices */
						for (x1 = 0; x1 < IMAGE_LINE; x1++) {
							/* unpack the 2 colors */
							/* map the low nibble first */
							c = xbuf[x1];
							ci = (int )(c & 0xf);
							for(z=0;z<2;z++) {
								p++;
								if (z==1)ci = (int )(c >> 4);

								if (ci == 0) {
									/* skip black pixels - buffers are initially black */
									if (p == 6) {
										p= -1;
										i+=2;
										j+=2;
									}
								}
								else {
								switch(p) {
									case 0: abuf[i]  = dhapix[ci][0]; 			/* 00001111 4 bits */
											break;
									case 1: abuf[i] = (abuf[i] | dhapix[ci][1]);/* 01110000 3 bits */
											mbuf[i] =  dhmpix[ci][1]; 			/* 00000001 1 bit  */
											break;
									case 2: mbuf[i] = (mbuf[i] | dhmpix[ci][2]);/* 00011110 4 bits */
											break;
									case 3: mbuf[i] = (mbuf[i] | dhmpix[ci][3]);/* 01100000 2 bits */
											abuf[j] =  dhapix[ci][3]; 			/* 00000011 2 bits */
											break;
									case 4: abuf[j] = (abuf[j] | dhapix[ci][4]);/* 00111100 4 bits */
											break;
									case 5: abuf[j] = (abuf[j] | dhapix[ci][5]);/* 01000000 1 bit  */
											mbuf[j] =  dhmpix[ci][5]; 			/* 00000111 3 bits */;
											break;
									case 6: mbuf[j] = (mbuf[j] | dhmpix[ci][6]);/* 01111000 4 bits */
											p = -1;
											i+=2;
											j+=2;
									}
								}
							}
						}
						target = DHRB[y1];
						/* display the scanline */
						#asm
							sta  $c055 ; AUX MEM
						#endasm
						movmem(abuf,target,40);
						#asm
							sta  $c054 ; MAIN MEM
						#endasm
						movmem(mbuf,target,40);
					}
					else {
						/* only 1 color - repeat = true */

						if (c == 0) { /* black */
							setmem(abuf,40,0);
							setmem(mbuf,40,0);
						}
						else {

							ci = (int )(c & 0xf); /* color indices 1-14 */

							if (ci == 15) { /* white */
								setmem(abuf,40,0x7f);
								setmem(mbuf,40,0x7f);

							}
							else {
								/* other colors */
								/* expand byte pairs to build scanline buffers */
								/* interleaf 7 pixels between main and aux memory */
								for (i = 0; i < 40; i++) {
									abuf[i] = dhrbytes[ci][0];
									mbuf[i] = dhrbytes[ci][1];
									i++;
									abuf[i] = dhrbytes[ci][2];
									mbuf[i] = dhrbytes[ci][3];
								}
							}
						}

						/* now write the pixels */
						target = DHRB[y1];
						#asm
							sta  $c055 ; AUX MEM
						#endasm
						movmem(abuf,target,40);
						#asm
							sta  $c054 ; MAIN MEM
						#endasm
						movmem(mbuf,target,40);
					}

					/* set to next line */
					x1 = 0;
					y1++;
					if (y1 >= IMAGE_LINES)break;
				}
			}
			else break;

			offset++;
		}
		if (y1 >= IMAGE_LINES)break;

     } while(offset<IMAGE_SIZE);

   close(fh);

   return 0;
}
