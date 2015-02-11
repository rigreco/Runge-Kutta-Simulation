/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : hibox.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Jan 9, 2010

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned HB[];

/* this version of fbox provides filled boxes in both hires palettes
   and conforms to the standard Apple II hires color numbers.
   it is not backwardly compatible due to my support for one
   palette only in the past. c'est la vie */

hibox(x1,y1,x2,y2,drawcolor)
int x1,y1,x2,y2,drawcolor;
{
    /* draws a filled box to the color specified */
    int packet = (x2-x1)+1;
    int temp,ctr;
    char *ptr;
    char c[2];

    /* if on an odd byte boundary reverse color arg */
    /* to match color mapping in the framebuffer    */
    if(x1%2!=0)
    {
        switch(drawcolor)
        {
            case 1 : drawcolor = 2; break;
            case 2 : drawcolor = 1; break;
            default: break;
        }
    }


    /* set the color */
    switch(drawcolor)
    {
      case 8 : break;                      /* inverse video box */
      case 7 : c[0]='\x7f'; c[1]='\x7f';   /* white  ... everything */
               break;
      case 6 : c[0]='\x2a'; c[1]='\x55';   /* green */
               break;
      case 5 : c[0]='\x55'; c[1]='\x2a';   /* purple */
               break;
      case 4:  c[0]='\x00';c[1]='\x00';    /* black  ... nothing */
               break;
      case 3 : c[0]='\xff'; c[1]='\xff';   /* white  ... everything */
               break;
      case 2 : c[0]='\xaa'; c[1]='\xd5';   /* orange */
               break;
      case 1 : c[0]='\xd5'; c[1]='\xaa';   /* blue */
               break;
      default: c[0]='\x80';c[1]='\x80';    /* black  ... nothing */
     }

   y2++;

   /* now write the pixels */
   while(y1<y2)
   {
     temp=HB[y1];
     ptr = (char *)(temp+x1);
     for(ctr=0;ctr<packet;ctr++)
     {
        if(drawcolor!=8)
        {
        *ptr=c[0];
        *ptr++;
        ctr++;
        if(ctr<packet)
        {
            *ptr=c[1];
            *ptr++;
        }
        }
        else
        {
        *ptr^='\x7f';   /* xor in current palette */
        *ptr++;
        }
     }
     y1++;
     }
}