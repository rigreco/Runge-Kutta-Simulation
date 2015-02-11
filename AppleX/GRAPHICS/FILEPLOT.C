/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : fileplot.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: April 13, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

plots2(str,x,y,color)
char *str;
int x,y,color;
{
    char c;
    if(color==4)x+=40;  /* set reverse video flag */

    if(str[0]!=0)
    {
    if(color!=0)
       while((c=*str++)!=0)plotchar2(c,x++,y);
    else
       while((c=*str++)!=0)plotchar2(' ',x++,y);
       }
}



