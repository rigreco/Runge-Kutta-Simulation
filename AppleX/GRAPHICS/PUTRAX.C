/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : putrax.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: May 29, 2008

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* decode RAG images with pcx run-length ecoding */
/* directly onto screen */
/* these are chunk oriented and do not break on scanlines */
/* but the header provides the width and height so no problem */
/* slightly more efficient to encode these in chunks since
   repeats spanning scanlines encode more efficiently.*/

/* a table containing the starting addresses of
   the 192 scanlines in HIRES PAGE 2 */
extern int HB[];


int put_rax(ptr,xorg, yorg)
unsigned char *ptr;
int xorg,yorg;
{
    char *crt;
	unsigned char ch;
	int x, x1, xcnt;
    int offset=0,width,height,target;

    width = *ptr++;
    height = *ptr++;
    target = (width * height);
    width = width + xorg;
    height = height + yorg;
    crt = (char *)(HB[yorg]+xorg);
    x1 = xorg;

	do{

	    ch=*ptr++;

	    /* check to see if its raw */
	    /* if its not, run encoded */
	    if(0xC0 == (ch & 0xc0)){
	       xcnt = 0x3f & ch;
	       ch = *ptr++;
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
					crt = (char *)(HB[yorg]+xorg);
				}
			}
			else break;

			offset++;
		}

		if (yorg >= height)break;

     } while(offset<target);
     return 0;
}

