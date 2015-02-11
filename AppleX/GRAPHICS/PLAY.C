/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : play.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 6, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

play(song)
char *song;
{
    char octave, note, duration;
    int ctr=0;

    while( (octave=song[ctr++])!=255)
    {

      note=song[ctr++];
      duration=song[ctr++];
      sound(octave,note,duration);
    }

}


