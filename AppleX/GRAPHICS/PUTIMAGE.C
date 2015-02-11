/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : putimage.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 7, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#define PUT 0    /* action verbs for putimage */
#define GET 1    /* expand as required */
#define P_STIX  2
#define P_BLACK 3
#define P_WHITE 4
#define P_AND   5

extern unsigned HB[];

/* handles screen manipulation of image fragments */
/* both gets and puts */
putimage(arrayname,width,height,xorg,yorg,action)
char *arrayname;
int width,height,xorg,yorg,action;
{
   int ctr=0;
   char *ptr,*ptr2;
   int temp;
   int bos=yorg+height;
   char tempbyte='\x80';


   if(action==P_WHITE)tempbyte='\xff';

   ptr = (char *)&arrayname[0];

   while(yorg<bos)
   {
     temp=HB[yorg];
     ptr2 = (char *)(temp+xorg);

     /* expand action verbs as required */
     switch(action)
     {                /* if the image byte is black don't erase the */
                      /* background                                 */
        case P_AND  : for(ctr=0;ctr<width;ctr++)
                      {
                       *ptr2|=*ptr;
                       *ptr2++;
                       *ptr++;
                       }
                       break;
        case P_STIX :
                      for(ctr=0;ctr<width;ctr++)
                      {
                        tempbyte=*ptr++;
                        if(tempbyte=='\x80'||tempbyte=='\x00')*ptr2++;
                        else *ptr2++=tempbyte;
                        }
                      break;

                   /* clear an area the size of the image fragment */
                   /* to black or white */
        case P_BLACK:
        case P_WHITE:
                      setmem((temp+xorg),width,tempbyte);
                      break;


                  /* read each raster into the buffer */
        case GET: movmem((temp+xorg),arrayname+ctr,width);
                  ctr+=width;
                  break;
        case PUT: /* read each raster to the screen */
        default :
                  movmem(arrayname+ctr,(temp+xorg),width);
                  ctr+=width;
     }
     yorg++;
     }
}


