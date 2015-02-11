/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : lofont.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Dec 4, 2009

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern char __chr[1096];

int lomsk[]={0x80,0x40,0x20,0x10,0x8,0x4,0x2,0x1};
int lofont(str,row,col,fg,bg,scale)
char *str;
int row,col,fg,bg,scale;
{
  int target, scanline, offset, r, r2, c, d, byte, nibble, x;
  unsigned char ch;


  if (scale > 2)scale = 1;

  target = strlen(str);
  for(scanline=0;scanline<8;scanline++)
  {

    /* set values for vertical term */
    /* expand x scale in the vertical direction */
    r = (scanline * scale) + row; /* max 16 high */
    if (r > 47)break;
    r2 = r + 1;

    /* run the string 8 times
       if scale =2 then print a double line
       each time which gives us a font of 16 high */
    for (byte=0;byte<target;byte++)
     {

      /* calculate the starting column for each
         run in the width of 7 pixels */
      c = (byte * 7) + col;
      if (c > 39)continue;

      d = str[byte]&0x7f;
      if (d < 32)d = 32;
      offset = ((d-32) * 8) + scanline;
      ch = __chr[offset];


      for (nibble=0;nibble<7;nibble++)
       {

        x = c+nibble;
        if (x > 39)break;

        if (ch & lomsk[6-nibble]){
		  setcolor(fg);
        }
        else {
		  if (bg < 0)continue;
		  setcolor(bg);
	    }
	    loplot(x,r);
	    if (scale > 1)loplot(x,r2);

       }

    }
  }
  return 0;

}
