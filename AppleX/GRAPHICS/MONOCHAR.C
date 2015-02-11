/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : monochar.c
Description  : G2 Library Routine
               Hi-Res 280 x 192 monochrome
               reasonably quick Font Routine
Written by   : Bill Buckels
Date Written : February 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
extern unsigned HB[];
extern char __chr[1096];

monochar(d,x,y,color)
{

int xoff, offset, y1, aux = 1;
unsigned char ch, *ptr;

  xoff = x/7;

  d &= 0x7f;
  if (d < 32)d = 32;

  for (y1 = 0; y1 < 8; y1++) {
	ptr = (unsigned char *) (HB[y] + xoff);
	y++;
	if (y > 191)break;
	offset = ((d-32) * 8) + y1;
	if (color > 0)ch = __chr[offset];
	else ch = __chr[offset]^0xff;
    *ptr = ch;
	}
}

monoplots(str,x,y,color,justify)
char *str,justify;
int x,y,color;
{
    unsigned d, idx = 0;

    if(str[0]!=0)
    {
	   /* centred text - Mid-Justify */
	   if (justify == 'm' || justify == 'M') {
		   idx = 0;
		   for (;;) {
			  idx++;
			  if (str[idx] == 0)break;
		   }
		   x -= ((idx * 7) / 2);
	   }

       while((d=*str++)!=0){
		   monochar(d,x,y,color); x+=7;
	   }
    }
}

