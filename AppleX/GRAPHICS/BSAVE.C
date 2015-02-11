/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : bsave.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: July 9, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* bsave a file from hires screen 2 */
#include <console.h>
#include <stdio.h>
#include <fcntl.h>
#include <prodos.h>
#include <sgtty.h>
#include <device.h>
#include <sysfunc.h>

bsave(savex)
char *savex;
{
    int fh;

    if((fh=bopen(savex, O_WRONLY|O_TRUNC|O_CREAT,0xc3)) != -1)
        {
        write(fh,(char *)0x4000,0x2000);
        close(fh);
        }
}


