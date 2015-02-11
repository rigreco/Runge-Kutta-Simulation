/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dmonchar.c
Description  : G2 Library Routine
               Double Hi-Res 560 x 192 monochrome
               reasonably quick Font Routine
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
extern unsigned DHRB[];
extern char *dhraux;
extern char __chr[1096];

dhmonochar(d,x,y,color)
{

int xoff, offset, y1, aux = 1;
unsigned char ch, *ptr;

#asm
    sta  $c054 ; MAIN MEM
#endasm

  if ((x%14) > 6) aux = 0;
  xoff = x/14;

  d &= 0x7f;
  if (d < 32)d = 32;

  for (y1 = 0; y1 < 8; y1++) {
	ptr = (unsigned char *) (DHRB[y] + xoff);
	y++;
	if (y > 191)break;
	offset = ((d-32) * 8) + y1;
	if (color > 0)ch = __chr[offset];
	else ch = __chr[offset]^0xff;
	if (aux!=0)*dhraux = 0; /* select auxiliary memory */
    *ptr = ch;
	}

/* reset to main memory */
#asm
    sta  $c054 ; MAIN MEM
#endasm

}

dmonoplots(str,x,y,color,justify)
char *str,justify;
int x,y,color;
{
    unsigned d, idx = 0;

    if(str[0]!=0)
    {
	   if (justify == 'm' || justify == 'M') {
		   idx = 0;
		   for (;;) {
			  idx++;
			  if (str[idx] == 0)break;
		   }
		   x -= ((idx * 7) / 2);
	   }

       while((d=*str++)!=0){
		   dhmonochar(d,x,y,color); x+=7;
	   }
    }
}

