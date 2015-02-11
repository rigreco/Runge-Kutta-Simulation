/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : getch.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: March 9, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

getch()
{
  char *KEYPRESS = (char*)0xC000;           /* return the last key press  */
  char *KEYCLEAR = (char*)0xC010;           /* clear the last key press   */
  char c;
            /* clear stragglers from the keyboard buffer */
            while((c=KEYPRESS[0]) > 127)KEYCLEAR[0]=0;

            /* read the keyboard buffer    */
            /* and return the character    */
            do{
               c = KEYPRESS[0];
               }while(c < 128);

               c-=128;
               KEYCLEAR[0]=0;
               return (int )c;
}

