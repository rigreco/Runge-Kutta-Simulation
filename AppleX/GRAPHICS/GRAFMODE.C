/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : fbox2.c
Description  : G2 Library Routine
			   For Hi-Res Mode

Written by   : Bill Buckels
Revision Date: January 9, 2010

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


#define PAGEONE  poke(49236,0)
#define PAGETWO  poke(49237,0)
#define TEXTMODE  0
#define GRAFMODE  2  /* graphics only */

setcrtmode(CRTMODE)
unsigned int CRTMODE;
{
    switch(CRTMODE)
        {
    case TEXTMODE:
                   poke(49233,0);
                   PAGEONE;
                   break;
    default  :
                  poke(49239,0);   /* hi res                    */
                  PAGETWO      ;   /* avoid prodos load address */
                  poke(49232,0);   /* set graphics              */
                  poke(49234,0);   /* full graphics */

        }

}
