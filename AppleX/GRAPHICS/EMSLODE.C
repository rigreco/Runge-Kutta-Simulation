/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : emslode.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 5, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */



/* the address of 2048 in main memory is used             */
/* for the ems signature which reserves 40 bytes          */
/* this is the first line of the text screen page 2       */
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


/* loads a library file */
emslode(name,libsize)
char *name;
unsigned libsize;
{
   int fh;
   int emscheck();
   unsigned int i;
   unsigned packet, straggler;
   unsigned himem,lomem;

   /* don't load the library if it's too big...               */
   /* don't load the library if it's in high memory already   */
   /* step 1... get the signature... this is the library name */
   /* if the library is already in memory this will likely be there  */
   /* when we exit we erase this to make sure. */

   /* step 2... compare and return -2 if it's already there */
   /* otherwise continue */

   if(libsize>46080)return -3;

   if(emscheck(name)!=0)return -2;

   if((fh = open(name,O_RDONLY,0xC3))==-1)
   {
    emsoff();
    return -1;
    }

   packet=    libsize/4000;         /* primary number of reads */
   straggler= libsize%4000;         /* remainder of reads      */

   himem = 0x0C00;
   lomem = 0x0C00+1096+24;

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
   close(fh);

   strcpy((char *)2048,name);
   /* Step 3... now do the signature... and return */
   return 0;

}



/* sign off the upper memory at 2048  */
/* the apple has no standard for this */
/* unlike the IBM LIM convention      */

emscheck(name)
char *name;
{
   char *sigbuf=(char *)2048;
   int target;

   unsigned int i;

   /* don't load the library if it's in high memory already   */
   /* step 1... get the signature... this is the library name */
   /* if the library is already in memory this will likely be there  */
   /* when we exit we erase this to make sure. */

   target=strlen(name);

   /* step 2... compare and return -2 if it's already there */
   /* otherwise return 0 */

   i=0;
   while(i<target)
   {
     if(name[i]!=sigbuf[i])return 0;
     i++;
     }

   return -2;
}


/* don't care what's there... unsign the ems when we leave */
/* that way we're not tripping over ourselves...           */
/* all we need to do is put zeros there...                 */
/* names don't contain zeros...                            */

emsoff()
{
   char *signoff=(char *)2048;
   int i=0;

   while(i++<40)*signoff++=0;
}
