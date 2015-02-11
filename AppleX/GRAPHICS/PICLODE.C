/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : piclode.c
Description  : G2 Library Routine
               For Hi-Res Mode

Written by   : Bill Buckels
Creation Date: June 5, 1991
Revised      : January 2013

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <fcntl.h>

extern unsigned HB[];

/* globals to override the load point for the image loader  */
char XPIC=0;
char YPIC=0;

int piclode(name)
char *name;
{
   int fh,y,y1=0,x1,bos,height,packet,c=-2;
   char tempchar[2];

   fh = open(name,O_RDONLY,0xc3); /* open a binary file */

   if (fh == -1)return -1;

   if (read(fh,tempchar,2)==2) {

	   packet= (int)tempchar[0];
	   height= (int)tempchar[1];

   		/* special case for fullscreen images first
	       always load from top left */
	   if (packet == 40) XPIC = 0;
   	   if (height == 192) YPIC = 0;
       if (packet == 40 && height == 160) YPIC = 0; /* fullscreen mixed text */

	   /* center the picture in the screen */
	   if(XPIC>39)
		  x1 = 20-(packet/2); /* break on even byte boundaries */
	   else
		  x1 = (int)XPIC;

	   if((x1%2)!=0)x1--;

	   if(YPIC>191)
		  y1=96-(height/2);
	   else
		  y1=(int)YPIC;

	   bos=y1+height;
	   if (bos > 192)bos = 192;

       /* Unbuffered read of each scanline = 192 reads for a full screen.
          this may not be terribly efficient for full screen images
          from a disk access perspective but may work quicker for small image
          fragments than RAX format encoded images.

          Consider encoding larger images in the RAX format if disk space
          is the greatest consideration.

          Consider leaving full screen images in a bsaved format if the
          loading is too slow and if a venetian-blind effect is acceptable.

          Also consider using the following routine and the rag format for
          everything if code size creates a memory problem and you just want
          one routine to save available memory. It may be your best
          all-around option.

          Keep in mind that you can use an overlay design for your program
          and put each loader in a separate overlay. There are 3 downsides to
          doing so: 1. overlays can be lost when programs are copied
                       by inexperienced users which will render your
                       app useless.
                    2. overlays need to be read from disk and the extra read
                       required by their use may slow down your loader.
                    3. the disk space that you save by reformatting a small
                       number of images into multiple formats may be
                       chewed-up by expanding your code size with multiple
                       loaders and complicating your life further (whether
                       you use overlays or just use multiple loaders).

          If you decide to use multiple loaders and you can avoid using
          overlays do so. Your program will run quicker and the bits and
          pieces (overlays) will not become hopelessly lost by some idiot
          which may even be you if you forget things like I do especially
          years later.

          A large non-trivial program like a paint program will likely
          need a number of overlays and support for multiple image
          formats. A trivial program like a slideshow or viewer will
          likely not need any overlays but will likely need mutiple
          format support.

          A final note. If you are using many images and image fragments
          take a look at the code in emsput which uses auxiliary memory
          to store RAG images that you preload when your program starts
          (or prior to viewing) and can be moved quickly directly to the screen.
          emsput can also be used to for sprite-like animation. RAX images
          can be expanded to RAG images and then stored in auxiliary memory
          and other neat stuff can be done like putting a bunch of
          concatanated RAG or RAX images into the auxiliary bank. Have a look at
          my ribcook program in the tools directory for some idea on
          how that can be done, and the code in emslode.c and the PLOGO.C code
          in Applex\SAMPLES\TIME for more information on how all this fits
          together.

          */
	   for(y=y1;y<bos;y++) {
		 c = read(fh,(unsigned char *)(HB[y] + x1),packet); /* read each raster to the screen */
		 if(c!=packet) break;
	   }
	   if (c != packet) c = -2;
	   else c = 0;
   }
   close(fh);

   /* zero our globals each time */
   XPIC=0;
   YPIC=0;

   return c;

}
