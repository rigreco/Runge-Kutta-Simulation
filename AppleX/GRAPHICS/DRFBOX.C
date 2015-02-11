/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : drfbox.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color routine
               Draws a filled box to the color specified
			   using double hi-res colors 0-15.
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned DHRB[];
extern unsigned char dhrbytes[16][4];

int dhrfbox(x1,y1,x2,y2,drawcolor)
int x1,y1,x2,y2,drawcolor;
{
    unsigned int temp;
    int y, x, packet, xorg, xend, prefix, postfix, idx, xoff;
    unsigned char mainbuf[40], auxbuf[40];

#asm
    sta  $c054 ; MAIN MEM
#endasm

    if (x1 < 0 || x2 > 139 || y1 < 0 || y2 > 191)return 0;

    /* convert pixels to 4 byte blocks and
       calculate pixels before blocks */

    prefix = x1;
    while ((prefix%7)!=0) prefix++; /* advance to left side */

    xorg = ((prefix / 7) * 4);

    idx = x2 + 1;
    xend = ((idx/7) * 4);

    /* assign packet length */
    idx = (xend-xorg);

    /* if box width does not include a full 4 byte block
       draw a filled box using a series of vertical lines */
    if(idx < 4) {
	   x2 += 1;
	   for (x = x1; x < x2; x++)dhrvline(x,y1,y2,drawcolor);
	   return 0;
	}

	packet = idx / 2;
	xoff = (xorg / 2);

   switch (drawcolor)
    {

		case 15:  /* white or black set the memory... */
		         setmem(auxbuf,packet,(unsigned char)0x7f);
			     setmem(mainbuf,packet,(unsigned char)0x7f);
			     break;
	    case 0:  setmem(auxbuf,packet,(unsigned char)0);
			     setmem(mainbuf,packet,(unsigned char)0);
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


   /* first write the horizontal pixel blocks */
   y = y1;
   y2++;
   while(y<y2)
   {
		temp=DHRB[y];
		#asm
			sta  $c055 ; AUX MEM
		#endasm
		movmem(auxbuf,(temp+xoff),packet);
		#asm
			sta  $c054 ; MAIN MEM
		#endasm
        movmem(mainbuf,(temp+xoff),packet);
	    y++;
	}
	y2--;

    /* now write the remaining pixels
       using a series of vertical lines
       expanding outward from the blocks */
	if (prefix != x1) {
	   x1--;
	   for (x = prefix;x > x1; x--) dhrvline(x,y1,y2,drawcolor);
	}

	postfix = ((xend / 4) * 7) - 1;
	if (postfix != x2) {
		x2++;
		for (x = postfix;x < x2; x++) dhrvline(x,y1,y2,drawcolor);
	}

return 0;
}

