/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : fbox.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 7, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern unsigned HB[];

fbox(x1,y1,x2,y2,drawcolor)
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
      case 4 : break;                      /* inverse video box */
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
        if(drawcolor!=4)
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

