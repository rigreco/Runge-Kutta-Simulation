/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dxblock.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color routine.
               Screen Width Color Block Line.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned DHRB[];
extern unsigned char dhrbytes[16][4];

/* produces screen width lines with only 1 color
   useful when called from my fullscreen XCrunched Image Decoder routines */
/* also handy for clearing the DHGR screen */
dxdblock(y, y2, color)
unsigned int y,y2,color;
{
	unsigned int target, a;
	int x;
	unsigned char mainbuf[40], auxbuf[40];

	if (color == 0) { /* black */
		setmem(auxbuf,40,0);
		setmem(mainbuf,40,0);
    }
    else {

	    a = color & 0xf; /* handles xcrunched colors and color indices 0-15 */

	    if (a == 15) { /* white */
			setmem(auxbuf,40,0x7f);
			setmem(mainbuf,40,0x7f);

		}
		else {
		    /* other colors */
			/* expand byte pairs to build scanline buffers */
			/* interleaf 7 pixels between main and aux memory */
			for (x = 0; x < 40; x++) {
				auxbuf[x]  = dhrbytes[a][0];
				mainbuf[x] = dhrbytes[a][1];
				x++;
				auxbuf[x]  = dhrbytes[a][2];
				mainbuf[x] = dhrbytes[a][3];
			}
		}
	}

    /* now write the pixels */
    y2++;
    while(y<y2)
    {
		target=DHRB[y];
		#asm
			sta  $c055 ; AUX MEM
		#endasm
		movmem(auxbuf,target,40);
		#asm
			sta  $c054 ; MAIN MEM
		#endasm
        movmem(mainbuf,target,40);
    	y++;
	 }
	 return 0;

}
