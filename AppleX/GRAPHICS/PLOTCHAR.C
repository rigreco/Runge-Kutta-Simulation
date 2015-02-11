/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : plotchar.c
Description  : G2 Library Routine

Revised by   : Bill Buckels
Revision Date: Jan 9, 2010

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

extern char __chr[1096];

plotchar(num,x,y)
char num,x,y;
{
  char *gs1=(char*)0x00;      /* pointer to address on hi-res page */
  int ybase,y1,z,a,yfin,y2,j;
  char whitey ='\xff';

     if(x>39)x-=40;
     else whitey='\x00';
     /* a reverse video flag... if x is 40 higher than it should be */

     for(j=0,y2=y;j<=7;++j,++y2){

		/* find address of char to be plotted */

		if (y2>=0 && y2<=63){
            ybase=0x4000;y1=y2;}
		else if (y2>=64 && y2<=127){
            ybase=0x4028;y1=(y2-64);}
		else if (y2>=128 && y2<=191){
            ybase=0x4050;y1=(y2-128);}

		z=y1/8;

		a=z*0x80+ybase;
		yfin=(y1-(z*8))*0x400 +a;

        if(!whitey)gs1[yfin+x]=__chr[(num-32)*8+j];
        else gs1[yfin+x]=(__chr[(num-32)*8+j]^whitey);
     }
}



