/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : plots.c
Description  : G2 Library Routine

Revised by   : Bill Buckels
Revision Date: April 5, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

plots(str,x,y,color)
char *str;
int x,y,color;
{
    char c;
    if(color==4)x+=40;  /* set reverse video flag */

    if(str[0]!=0)
    {
    if(color!=0)
       while((c=*str++)!=0)plotchar(c,x++,y);
    else
       while((c=*str++)!=0)plotchar(' ',x++,y);
       }
}


