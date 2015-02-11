/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dhrfont.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color font routine
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
extern char __chr[1096];

int msk7[]={0x1,0x2,0x4,0x8,0x10,0x20,0x40};
int dhrfont(str,row,col,fg,bg,scale,pitch,justify)
char *str;
int row,col,fg,bg,scale,pitch;
char justify;
{
  int target, scanline, offset, r, r2, c, d, byte, nibble, x, spaces = 0;
  unsigned char ch;

  if (scale > 2)scale = 1;
  if (pitch != 6)pitch = 7;

  target = strlen(str);

  for (byte=0;byte<target;byte++) {
        d = str[byte]&0x7f;
        if (d < 32)d = 32;
        if (d == 32 || d == 'l' || d == '1' || d == '.' || d == '!')spaces +=1;
  }

  if (justify == 'm' || justify == 'M') {
      offset = ((target * pitch)- spaces)/2;
      col = col - offset;
  }

  for(scanline=0;scanline<8;scanline++)
  {

    /* set values for vertical term */
    /* expand x scale in the vertical direction */
    r = (scanline * scale) + row; /* max 16 high */
    if (r > 191)break;
    r2 = r + 1;

    /* run the string 8 times
       if scale = 2 then print a double line
       each time which gives us a font of 16 high */
    spaces = 0;
    for (byte=0;byte<target;byte++)
     {

      /* calculate the starting column for each
         run in the width of 6 or 7 pixels */
      c = ((byte * pitch) + col)-spaces;
      if (c > 139)continue;

      d = str[byte]&0x7f;
      if (d < 32)d = 32;
      if (d == 32 || d == 'l' || d == '1'|| d == '.'||d == '!')spaces +=1;

      if (d == 32 && bg < 0)continue;

      offset = ((d-32) * 8) + scanline;
      ch = __chr[offset];

      if (ch == 0 && bg < 0)continue;

      for (nibble=0;nibble<pitch;nibble++)
       {

        x = c+nibble;
        if (x > 139)break;

        if (ch & msk7[nibble]){
		  if (scale > 1 && r2 < 192)
		  	dhrvline(x,r,r2,fg);
		  else
		  	dhrvline(x,r,r,fg);

        }
        else {
		  if (bg < 0)continue;
		  if (scale > 1 && r2 < 192)
		  	dhrvline(x,r,r2,bg);
		  else
		  	dhrvline(x,r,r,bg);

	    }

       }

    }
  }
  return 0;

}
