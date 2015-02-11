/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : kbhit.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 29, 2008

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


kbhit()
{
  char *KP = (char*)0xC000;
  char c;

  /* read the keyboard buffer    */
  /* and return 0 if no character is waiting */

   c = KP[0];
   if(c<128)return 0;
   return (int)c-128;
}

