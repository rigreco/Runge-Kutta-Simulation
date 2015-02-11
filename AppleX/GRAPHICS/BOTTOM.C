/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : bottom.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: Jan 9, 2010

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* some functions to output text directly to the screen */


extern int textbase[24];

clear_text(ch, page,bottom,reverse)
char ch;
int page, bottom,reverse;
{
	char *crt;
	int row, col;
    int offset = 0;
    int r1 = 0;

    if (page !=0)offset = 1024;
    if (bottom != 0)r1 = 20;

    ch = ch &0x7f;
    if (reverse == 0) ch += 128;

	for (row = r1; row < 24; row++) {
	  crt = (char *)(textbase[row] + offset);
      for (col = 0; col < 40; col++) {
	     *crt++ = ch;
	  }
    }
}

clear_top()
{
	clear_text(' ',1,0,0);
}

clear_bottom()
{
    clear_text(' ',1,1,0);
}


/* row = 0,0 to 3,39 in split screen mode */
/* I am just going directly to the text screen address */
/* and outputting a raw ascii value */
print_bottom(str,row,col)
char *str;
int row, col;
{
    print_text(str,row,col,1,1,0);
}

print_top(str,row,col)
char *str;
int row, col;
{
    print_text(str,row,col,1,0,0);
}

print_text(str,row,col,page,bottom,reverse)
char *str;
int row,col,page,bottom,reverse;
{
     char *crt;
     char c;
     int offset = 0;

     if (col > 39) {
	    col-=40;
	    reverse = 1;
	 }
     if (bottom != 0)row+=20;
     if (page !=0) offset = 1024;
     if (reverse != 0)reverse = 0;
     else reverse = 128;

     crt = (char *)(textbase[row]+offset+col);

     while((c=*str++)!=0)*crt++=(c+reverse);
}