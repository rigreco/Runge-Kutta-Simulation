/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dlodelo.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Dec 29, 2012

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <fcntl.h>

/* the following loads two non-compressed
   graphics image formats associated with
   double lores mode...

   Single File Raster Format - DLO
   2 Part Bsaved Image Format - DL1 and DL2


   for bsaved images the convention of calling
   the second image a .DL2 file is supported in
   this loader when loading a 2 part image...


   the load is split in the middle after loading
   the first half into auxilliary memory */


extern char *dhrmain;
extern char *dhraux;


/* The following buffer is not very elegant but necessary I am afraid... when I tried to do a raw read
   into screen memory some funky conflict was happening between ProDOS and screen memory and nothing would display.

   So I separated my read operations from my display operations hence the buffer, unlike in the DOS 3.3 version
   which reads directly to the screen.

*/

char lodebuf[1920];

int dlodelo(name)
char *name;
{
   int fh, y, status=-2;
   int c, fl = 1016, height, packet, jdx, idx;
   char tempchar[2], name1[20], name2[20], *ptr1, *ptr2;
   unsigned temp;

   ptr1 = (char *)&lodebuf[0];
   ptr2 = (char *)&lodebuf[40];

   jdx = 999;
   for (idx = 0; name[idx] != 0; idx++) {
        name1[idx] = name[idx];
        name2[idx] = name[idx];
		if (name[idx] == '.') {
			name1[idx] = 0;
			name2[idx] = 0;
			jdx = idx;
			break;

		}
   }
   if (jdx == 999) return status;

   strcat(name2,".DL1");

   /* start in main memory - page1 */
   *dhrmain = 0;
   fh = open(name2,O_RDONLY,0x3C); /* open a binary DL1 file */
   /* if we can't open a DL1 we must be loading a raster file
      so open a DLO file... and if we can't open that
      just fail... I don't want garbage in here so
      I don't support creative naming... */
   if (fh == -1) {
	   strcat(name1,".DLO");
	   fl = 1922;
	   /* main memory - page1 */
	   *dhrmain = 0;
	   fh = open(name1,O_RDONLY,0x3C);
	   if (fh == -1) {
		  /* main memory - page1 */
	      *dhrmain = 0;
	      return -1;
	   }
   }
   else {
	   /* if we opened a DL1 then get ready to open a DL2 */
	   strcat(name1,".DL2");
   }

   switch(fl) {
	   case 1922:
	        /* is it a DLO ? */
			c = read(fh,tempchar,2);
			if (c!=2) {
				close(fh);
				break;
			}
			packet= (int)tempchar[0];
			height= (int)tempchar[1];
			if (height != 24 || packet != 80) {
				close(fh);
				break;
			}
			c = read(fh,lodebuf,1920);
			close(fh);
			if (c!=1920)break;
            status = 0;

            idx = 0;

            /* The following is not very elegant I am afraid... but when I tried to do this
               in a loop using an address array like in the DOS 3.3 version I kept hitting some kind of limitation
               so I used constants and an onerous code-block instead which worked... so here it is...

            */
            dhraux[0] = 0; movmem(ptr1+idx,0x0400,40); /* switch to auxilliary memory - page2 */
            dhrmain[0] = 0; movmem(ptr2+idx,0x0400,40);/* switch back to main memory - page1 */
            idx += 80;

            dhraux[0] = 0; movmem(ptr1+idx,0x0480,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0480,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0500,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0500,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0580,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0580,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0600,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0600,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0680,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0680,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0700,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0700,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0780,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0780,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0428,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0428,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x04A8,40); dhrmain[0] = 0; movmem(ptr2+idx,0x04A8,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0528,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0528,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x05A8,40); dhrmain[0] = 0; movmem(ptr2+idx,0x05A8,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0628,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0628,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x06A8,40); dhrmain[0] = 0; movmem(ptr2+idx,0x06A8,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0728,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0728,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x07A8,40); dhrmain[0] = 0; movmem(ptr2+idx,0x07A8,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0450,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0450,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x04D0,40); dhrmain[0] = 0; movmem(ptr2+idx,0x04D0,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0550,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0550,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x05D0,40); dhrmain[0] = 0; movmem(ptr2+idx,0x05D0,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0650,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0650,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x06D0,40); dhrmain[0] = 0; movmem(ptr2+idx,0x06D0,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x0750,40); dhrmain[0] = 0; movmem(ptr2+idx,0x0750,40); idx += 80;
            dhraux[0] = 0; movmem(ptr1+idx,0x07D0,40); dhrmain[0] = 0; movmem(ptr2+idx,0x07D0,40);
			break;

	   case 1016:
	       /* is it a bsaved image */
	       c = read(fh,lodebuf,1016);
	       close(fh);
	       if (c != 1016)break;

    	   /* switch to auxilliary memory - page2 */
		   *dhraux = 0;
		   movmem(ptr1,0x0400,1016);

           /* switch back to main memory - page1 */
		   *dhrmain = 0;
		   fh = open(name1,O_RDONLY,0x3C); /* open a binary DL2 file */
           if (fh == -1) {
			   status = -1;
			   break;
		   }
	       c = read(fh,lodebuf,1016);
	       close(fh);
	       if (c != 1016)break;

		   /* switch back to main memory - page1 */
		   *dhrmain = 0;
           movmem(ptr1,0x0400,1016);

           status=0;
		   break;
   }

   /* switch back to main memory - page1 */
   *dhrmain = 0;

   return status;
}

