/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : emsput.c
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
#define P_XOR   6



/* emsputimage() */
/* handles screen manipulation of image fragments             */
/* both gets and puts and uses ems memory for the IO buffer   */
/* for screen puts other than memory moves a buffer is used   */

/* since a full screen stored in our .BOT format has a
   file size of 7680 bytes there is room in the upper ram bank
   to store 6 full screens (6x7680=46080 bytes) */


extern unsigned HB[];

emsputimage(emsarraybase,width,height,xorg,yorg,action)
unsigned emsarraybase;
int width,height,xorg,yorg,action;
{
   int ctr;
   char *ptr,*ptr2;
   int temp;
   /* the ems buffer starts above the 2nd page of text screen */
   /* in auxiliary memory */

   unsigned hitemp=emsarraybase+0x0C00;
   int bos=yorg+height;
   char tempbyte='\x80';
   char arrayname[40] ;

   if(action==P_WHITE)tempbyte='\xff';


   while(yorg<bos)
   {
     temp = HB[yorg];

     ptr = (char *)&arrayname[0];
     ptr2 = (char *)(temp+xorg);

     /* expand action verbs as required */
     switch(action)
     {
        case P_XOR  : /* reverse video */
                      auxtomain(hitemp,hitemp+width-1,&arrayname[0]);

                      for(ctr=0;ctr<width;ctr++)
                      {
                       *ptr2=(*ptr^0x7f);
                       *ptr2++;
                       *ptr++;
                       }
                       break;


                      /* bitwise ANDing the background... */
                      /* works best with white */
        case P_AND  :
                      auxtomain(hitemp,hitemp+width-1,&arrayname[0]);

                      for(ctr=0;ctr<width;ctr++)
                      {
                       *ptr2|=*ptr;
                       *ptr2++;
                       *ptr++;
                       }
                       break;

                      /* if the image byte is black don't erase the */
                      /* background                                 */
        case P_STIX :
                      auxtomain(hitemp,hitemp+width-1,&arrayname[0]);

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
                      for(ctr=0;ctr<width;ctr++)*ptr2++=tempbyte;break;


                  /* read each raster into ems */
        case GET:  maintoaux((temp+xorg),(temp+xorg+width-1),hitemp);
                   break;

        case PUT: /* read each raster to the screen */
        default :  auxtomain(hitemp,hitemp+width-1,(temp+xorg));
                   break;
     }
     yorg++;
     hitemp+=width;
     }
}


