/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : fbox2.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 7, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */



extern unsigned HB[];

flood(x1,y1,x2,y2,drawcolor)
int x1,y1,x2,y2,drawcolor;
{

    /* draws a filled box to the color specified */

    int packet = (x2-x1)+1;
    int temp,ctr;
    char *ptr;
    char c[40];

    y2++;
    if(x1%2!=0)
    {
      switch(drawcolor)
      {
        case 5:drawcolor=6;break;
        case 6:drawcolor=5;break;
        case 2:drawcolor=1;break;
        case 1:drawcolor=2;
        }
    }

    /* set the color */
    switch(drawcolor)
    {
      case 5 : c[0]='\xd5'^0xff; c[1]='\xaa'^0xff;   /* green   */
               break;

      case 6 : c[0]='\xaa'^0xff; c[1]='\xd5'^0xff;   /* violet  */
               break;

      case 2 : c[0]='\xaa'; c[1]='\xd5';             /* orange  */
               break;

      case 1 : c[0]='\xd5'; c[1]='\xaa';             /* blue    */
               break;

      case 4 : while(y1<y2)     /* inverse video */
               {
                temp=HB[y1];
                ptr = (char *)(temp+x1);
                ctr = 0;
                while(ctr<packet)
                   {
                     *ptr^='\x7f';
                     *ptr++;
                      ctr++;
                   }
               y1++;
               }
               return 0;

      /* white or black set the memory...   */
      case 3 : drawcolor =255;   /* white   */
      default:
                                 /* black   */
               while(y1<y2)
               {
                temp=HB[y1];
                setmem((temp+x1),packet,(char)drawcolor);
                y1++;
                }

     }


   /* fill the buffer if blue, orange, green, or violet */

     ptr=(char *)&c[2];
     ctr=2;

     while(ctr<packet)
     {
        *ptr++=c[0];
        ctr++;
        if(ctr<packet)*ptr++=c[1];
        ctr++;
        }

   /* now write the pixels */
   while(y1<y2)
   {
     temp=HB[y1];
     movmem(c,(temp+x1),packet);
     y1++;
     }

return 0;

}


