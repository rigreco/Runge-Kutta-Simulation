/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dxline.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color routine.
               Screen Width Color Pixel Line.

               Input 70 bytes with aux color indices in low nibble
               and main colors in high nibble. Lo-Res color order.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned DHRB[];
extern unsigned char dhapix[16][7];
extern unsigned char dhmpix[16][7];


dxdline(y, ptr)
int y;
unsigned char *ptr;
{
	unsigned int target = DHRB[y];
	register int x, z, i=0, j=1, ci, p=-1;
	unsigned char mbuf[40],abuf[40],c;

    /* set buffers to black */
    setmem(abuf,40,0);
    setmem(mbuf,40,0);

	/* decode the scanline indices */
	for (x = 0; x < 70; x++) {
		/* unpack the 2 colors */
		/* map the low nibble first */
		c = ptr[x];
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


