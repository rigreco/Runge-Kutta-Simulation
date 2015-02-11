/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : drflood.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color routine
               Draws a filled box to the color specified
			   using double hi-res colors 0-16.
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
/* note: the original version of dhrflood which was distributed with
         the DOS 3.3 G3 Library was buggy. this version is called in pixels
         also but works only in 4 byte blocks. */

/* consider using dhrfbox instead of this routine unless you are not doing
   other plotting and you want to do something like clear the screen which
   does not require pixel level accuracy */

extern unsigned DHRB[];
extern unsigned char dhrbytes[16][4];
extern char *dhrmain;
extern char *dhraux;

int dhrflood(x1,y1,x2,y2,drawcolor)
int x1,y1,x2,y2,drawcolor;
{

    /* draws a filled box to the color specified */
    /* using double hi-res colors 0-16 */
    unsigned int temp;
    int x, packet, xorg, xend, idx, xoff;
    unsigned char *ptr, mainbuf[40], auxbuf[40];

#asm
    sta  $c054 ; MAIN MEM
#endasm

    if (x1 < 0 || x2 > 139 || y1 < 0 || y2 > 191)return 0;

    /* convert pixels to 4 byte blocks - for now */

    x = x1;
    while ((x%7)!=0) x ++; /* advance to left side of box */

    xorg = ((x / 7) * 4);

    idx = x2 + 1;
    xend = ((idx/7) * 4);

    /* assign packet length */
    idx = (xend-xorg);

    if(idx < 4) return 0;

    packet = idx / 2;
    xoff = (xorg / 2);

    if (drawcolor < 1 || drawcolor > 16) drawcolor = 0;

    switch (drawcolor)
    {
		case 16:
		    /* pseudo-color 16 */
    		/* inverse video */
    		y2++;
			while(y1<y2)
			{
				temp=DHRB[y1];
				ptr = (unsigned char *)(temp+xoff);
				idx = 0;
				#asm
					sta  $c055 ; AUX MEM
				#endasm
				while(idx<packet)
				{
					*ptr = *ptr^'\x7f';
					*ptr++;
					idx++;
				}
				#asm
					sta  $c054 ; MAIN MEM
				#endasm
				ptr = (unsigned char *)(temp+xoff);
                idx = 0;
				while(idx<packet)
				{
					*ptr = *ptr^'\x7f';
					*ptr++;
					idx++;
				}
				y1++;
			}
			return 0;	/* outa here */

		case 15:  /* white or black set the memory... */
		         setmem(auxbuf,packet,0x7f);
			     setmem(mainbuf,packet,0x7f);
			     break;
	    case 0:  setmem(auxbuf,packet,0);
			     setmem(mainbuf,packet,0);
			     break;

		default:
		    /* other colors */
			/* expand byte pairs to build scanline buffers */
			/* interleaf 7 pixels between main and aux memory */
			for (idx = 0; idx < packet; idx++) {
				auxbuf[idx]  = dhrbytes[drawcolor][0];
				mainbuf[idx] = dhrbytes[drawcolor][1];
				idx++;
				auxbuf[idx]  = dhrbytes[drawcolor][2];
				mainbuf[idx] = dhrbytes[drawcolor][3];
			}


	}

   /* now write the pixels */
   y2++;
   while(y1<y2)
   {
		temp=DHRB[y1];
		#asm
			sta  $c055 ; AUX MEM
		#endasm
		movmem(auxbuf,(temp+xoff),packet);
		#asm
			sta  $c054 ; MAIN MEM
		#endasm
        movmem(mainbuf,(temp+xoff),packet);
    	y1++;
	}

return 0;
}

