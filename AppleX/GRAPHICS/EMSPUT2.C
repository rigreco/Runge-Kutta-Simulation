/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : emsput2.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 19, 2008

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



/* emsputpart() */
/* handles screen manipulation of image fragments             */
/* both gets and puts and uses ems memory for the IO buffer   */
/* for screen puts other than memory moves a buffer is used   */

/* since a full screen stored in our .BOT format has a
   file size of 7680 bytes there is room in the upper ram bank
   to store 6 full screens (6x7680=46080 bytes) */


extern unsigned HB[];



/* this special version of emsputimage can be used for the same purpose
   as emsputimage and additionally can be used for displaying part of an
   image. 1 extra argument is required (partwidth).

   1. to use normally, partwidth (the display width) is the same as width
      and all other values are the same as emsputimage.

   2. to use to display part of an image some additional calculations are
      done outside of here. Arguments that always remain the same are:

      width - this is required to evenly increment to the byte origin
              of the next raster in any image buffer.

      xorg, yorg, action - these don't change since they define where and
                           how the image will be diplayed.

      The partwidth argument will be different than the width argument if
      the part-image width is less than the base image width.

      Since partwidth is display width, it's value is the width in bytes
      of the portion of the raster required for display

      height can vary if diplaying a part-image less than the height of
      the original image.

      Calculations are required for the starting offset into the image:

      emsarraybase - the starting byte of the first raster in the part-image is
      added to the usual offset for the base image. common sense in calculating
      this offset must be used to avoid going beyond the memory bounds of the
      base image.

      if displaying a partimage that is the same height as the original image,
      this additional value will be equal to or less than (width - partwidth)
      and the height will remain the same.

      if getting fancy by displaying different heights and so forth, the partimage
      offset is calculated by adding (rasters * width) to the base of the array to
      get to the start of the load raster, then the offset to the first byte for
      display is added. take care to make sure that height is adjusted accordingly
      so the display does not go beyond the bounds of the base image.

      */


emsputpart(emsarraybase,width,height,xorg,yorg,action,partwidth)
unsigned emsarraybase;
int width,height,xorg,yorg,action,partwidth;
{
   int ctr;
   char *ptr,*ptr2;
   int temp;
   /* the ems buffer starts above the 2nd page of text screen */
   /* in auxilliary memory */

   /* offset into the array to the starting byte of the
      part-image and then increment the offset by the width of
      the whole image */
   unsigned hitemp=emsarraybase+0x0C00;
   int bos=yorg+height;
   char tempbyte='\x80';
   char arrayname[40] ;

   if(action==P_WHITE)tempbyte='\xff';

   /* despite the fact that we are incrementing by the
      whole image width, we only move the part-image
      to the display or from the display */

   while(yorg<bos)
   {
     temp = HB[yorg];

     ptr = (char *)&arrayname[0];
     ptr2 = (char *)(temp+xorg);

     /* expand action verbs as required */
     switch(action)
     {
        case P_XOR  : /* reverse video */
                      auxtomain(hitemp,hitemp+partwidth-1,&arrayname[0]);

                      for(ctr=0;ctr<partwidth;ctr++)
                      {
                       *ptr2=(*ptr^0x7f);
                       *ptr2++;
                       *ptr++;
                       }
                       break;


                      /* bitwise ANDing the background... */
                      /* works best with white */
        case P_AND  :
                      auxtomain(hitemp,hitemp+partwidth-1,&arrayname[0]);

                      for(ctr=0;ctr<partwidth;ctr++)
                      {
                       *ptr2|=*ptr;
                       *ptr2++;
                       *ptr++;
                       }
                       break;

                      /* if the image byte is black don't erase the */
                      /* background                                 */
        case P_STIX :
                      auxtomain(hitemp,hitemp+partwidth-1,&arrayname[0]);

                      for(ctr=0;ctr<partwidth;ctr++)
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
                      for(ctr=0;ctr<partwidth;ctr++)*ptr2++=tempbyte;break;


                  /* read each raster into ems */
        case GET:  maintoaux((temp+xorg),(temp+xorg+partwidth-1),hitemp);
                   break;

        case PUT: /* read each raster to the screen */
        default :  auxtomain(hitemp,hitemp+partwidth-1,(temp+xorg));
                   break;
     }
     yorg++;
     hitemp+=width; /* increment offset by total array width */
     }
}


