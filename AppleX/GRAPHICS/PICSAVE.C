/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : picsave.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: June 5, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* picsave a file from hires screen 2 */

#include <console.h>
#include <stdio.h>
#include <fcntl.h>
#include <prodos.h>
#include <sgtty.h>
#include <device.h>
#include <sysfunc.h>

extern unsigned HB[];
picsave(savex)
char *savex;
{
     int fh;
     int y;
     char tempchar[2];

    if((fh=bopen(savex, O_WRONLY|O_TRUNC|O_CREAT,0xc3)) != -1)
        {
        tempchar[0]=40;
        tempchar[1]=192;
        write(fh,tempchar,2);

        for(y=0;y<192;y++)
         write(fh,(char *)(HB[y]),40); /* write each raster */
        close(fh);
         }

}


