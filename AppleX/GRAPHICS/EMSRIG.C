/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : emsrig.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 26, 2008

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* loads a rag from an open rib to himem */
/* assumes that the rib contains rags and only rags
   and that they are all the same size */
/* emsputimage can then be used to display the image */


/* the ems buffer start is set to 0x0C00 in aux memory    */

/* this is the area directly above the secondary page of video ram    */
/* the auxilliary memory map for the apple 2C indicates that areas    */
/* below this have memory "holes" which are reserved or assigned even */
/* though zero page and the hardware stack finish at 0x200            */

/* in Main Memory... */
/* a 4000 byte buffer is used above where we store the font   */
/* at 0x0C00+1096+24 =4192 as a temporary IO buffer           */
/* to transfer the data to the upper ram banks                */
/* this avoids text screen page 2 and is below the prodos load address */


#include <stdio.h>
#include <fcntl.h>
#include <prodos.h>
#include <sgtty.h>
#include <device.h>
#include <sysfunc.h>


emsrig(fh,pos,width,height,emsarraybase)
int fh, pos, width,height;
unsigned emsarraybase;
{
   long lpos;
   unsigned packet, straggler, lomem, himem, ragsize, i;

   ragsize = width * height;

   lpos = (long)ragsize;
   lpos = lpos * (long)pos;

   /* seek to the image */
   /* lseek(fh, lpos, 0);*/

   packet=    ragsize/4000;         /* primary number of reads */
   straggler= ragsize%4000;         /* remainder of reads      */

   lomem = 0x0C00+1096+24;
   himem=emsarraybase+0x0C00;

   /* do the bulk of the work and then the remainder */
   i=0;
   while(i<packet)
   {
   read(fh,(char *)lomem,4000);
   maintoaux(lomem,lomem+4000-1,himem);
   himem+=4000;
   i++;
   }

   if(straggler>0)
   {
   read(fh,(char *)lomem,straggler);
   maintoaux(lomem,lomem+straggler-1,himem);
   }


   return 0;

}


