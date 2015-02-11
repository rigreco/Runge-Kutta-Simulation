/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : sound.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 6, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */



/* create a proper musical scale for the apple */
/* this is the algorithm that will be used     */
/* june 1991 */
/* tired of flat notes... select a piano scale */

/* Apple Pitch Values  */

int __pitch[5][12]={

/* C    C#    D    D#     E     F    F#     G    G#   A   A#   B */
/* 0    1     2    3      4     5    6      7    8    9   10  11 */

285, 270, 257, 243, 229, 215, 200, 188, 179, 171, 167, 160,
150, 142, 132, 126, 117, 111, 106,  99,  93,  88,  83,  79,
74,  70,  65,  61,  58,  55,  51,   48,  45,  43,  40,  38,
36,  34,  32,  30,  28,  26,  24,   23,  21,  20,  19,  18,
17,  34,  32,  30,  28,  26,  24,   23,  21,  20,  19,  18};

sound(octave,note,duration)
char octave,note,duration;
{
    int j,pit,temp;

    switch(octave)
    {
      case 0:
      case 1: pit= __pitch[0][note];break;

      case 2: pit= __pitch[1][note];break;
      case 3: pit= __pitch[2][note];break;

      case 4: pit= __pitch[3][note];break;
      case 5:
      case 6: pit= __pitch[4][note];break;

      /* silence... try to match the sound loop */
      case 7: pit= 128;
              temp=(1024*duration)/pit;
              NOPER:;  /* loop the required note length */
                     j=pit;
              COUNTING:;
                     if(j--)goto COUNTING;
                     if(temp--)goto NOPER;
              return 0;
            }
temp=(1024*duration)/pit;

TOPPER:;  /* loop the required note length */
#asm
        BIT $C030
#endasm
        j=pit;
COUNTER:;
        if(j--)goto COUNTER;
        if(temp--)goto TOPPER;

        /* wait for the duration specified by pitch */
        /* then click it again                      */

}




