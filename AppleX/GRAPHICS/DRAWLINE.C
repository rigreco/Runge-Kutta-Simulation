/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : dlopixel.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: May 20, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#define BOX '\x01'

drawline(x1, y1, x2, y2, dcolor,action)
int x1, y1, x2, y2, dcolor;
char action;
{

   /* make  sure x2 is greater than x1 */
   int temp;
   if(x1 > x2)
   {
     temp=x1;
     x1 = x2;
     x2 = temp;
     temp = y1;
     y1 = y2;
     y2 = temp;
    }


   switch(dcolor)
   {


     case 1 : if(action==BOX)
              {
              bdrw(x1,y1,x2,y1);
              blineto(x2,y2);
              blineto(x1,y2);
              blineto(x1,y1);
              break;
              }
              bdrw(x1,y1,x2,y2);
              break;

     case 2 : if(action==BOX)
              {
              rdrw(x1,y1,x2,y1);
              rlineto(x2,y2);
              rlineto(x1,y2);
              rlineto(x1,y1);
              break;
              }
              bdrw(x1,y1,x2,y2);
              break;

     default: if(action==BOX)
              {
              drw(x1,y1,x2,y1);
              lineto(x2,y2);
              lineto(x1,y2);
              lineto(x1,y1);
              break;
              }
              drw(x1,y1,x2,y2);

    }

}

