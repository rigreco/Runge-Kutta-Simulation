/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : fbox2.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: December 24, 2012

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
#include <g3.h>


/* Does not work with double res modes or for mixing 80
   column text with standard hi-res and lo-res graphics
   modes...

   I have developed alternate single purposes routines which
   in the end keep the code size smaller and are more
   efficient than a kitchen-sink routine like this one.

   Use those instead following the code samples that I have
   provided.

   */

setcrtmodex(CRTMODE)
unsigned int CRTMODE;
{
    switch(CRTMODE)
        {
     case TEXTMODE:
                   poke(49233,0);
                   PAGEONE;
                   break;


    case LORES:
                  poke(49238,0);   /* lo res */
                  PAGEONE;
                  poke(49232,0);   /* set graphics */
                  poke(49234,0);   /* full graphics */
                  loclear();
                  break;

    case GRAFMODE:
    default  :
                  poke(49239,0);   /* hi res */
                  PAGETWO;         /* avoid prodos load address */
                  poke(49232,0);   /* set graphics */
                  poke(49234,0);   /* full graphics */

        }

}
