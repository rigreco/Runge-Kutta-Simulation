/* Copyright (C) 2013 Riccardo Greco rigreco.grc@gmail.com.
*   
*  This project is based on 1999-2000 Thesis work of Greco Riccardo.
*  It implement an Runge Kutta 4(5)^ order integration numerical method of differential equations set
*  by use of double precision floating point operation in Aztec C65 language.
*  It allow to simulate different mathematical models such as:
*  Resistance Capacitor electrical circuit, Direct Current electric motor,
*  Alternative Current three phase induction motor.
*  
*  Thanks to Bill Buckels for his invaluable support:
*  Aztec C compilers http://www.aztecmuseum.ca/compilers.htm
*/
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include "d2monplt.h"

/* GENERAL GLOBAL */
extern double h,keep;
extern char fbuf[80];
extern int cnt,fd; /* x FILE LOW lEVEL DON'T FORGET THIS */ 
extern struct data {
					char v[20];
					char i[20];
					};

/* LOCAL GLOBAL */
char *FILE_NAME="dcrk";

ovmain()
{

double nc,ia,w,xscale,iscale,wscale;
int plotx,ploty,plotey,ic,px,py,;
struct data rk;
double atof(); /* DON'T FORGET THIS */
char tx[4];
	/* inizialization */
	
	px=(int)0.0;
    py=(int)0.0;
	ic=(int)0.0;
	xscale=(double)100.0;  /* set x scale plot */
	iscale=(double)1.0;	/* set y (ia(t)) scale plot */
	wscale=(double)0.5;	/* set y (w(t)) scale plot */
	nc=(double)0.0;
		
							
		/* GRAPHICS SECTION */		
					
		/* Axes */ 
		for (px=0,py=96;px<=560;++px)
		{
			d2monoplot(px,py,py,1);
		}  /*Axis X */
		
					
	/*	for (px=0,py=0;py<=192;++py)
		{
			d2monoplot(px,py,py,1);
		} /* Axis Y */
		
				
		/* labels */
		monoplots("t=",505,36,1,'M');
		monoplots("ia(t)=",25,0,1,'M');
		monoplots("w(t)=",25,10,1,'M');
						
		/* read first recort (header) for increment file pointr */
		open(FILE_NAME,O_RDONLY,0xC3);
		read(fd,fbuf,80);
			
		/* Main Plot */
		for (ic=0;ic<cnt;ic++)
		{
			/* read data fromfile */
			read(fd,rk.v,20); /* read ia(t) */
			read(fd,rk.i,20); /* read w(t) */
					
			/* save data in doubles */
			ia=(double)atof(rk.v);
			w=(double)atof(rk.i);
				    
		    /* presentation data*/
			monoplots(rk.v,110,0,1,'M');
			monoplots(rk.i,110,10,1,'M');
			ftoa(nc,tx,2,1);
			monoplots(tx,535,36,1,'M');
		
			/* plot graph of data*/
			plotx=(int)((nc*xscale)+1);
			ploty=(int)((-ia*iscale)+95);
			d2monoplot(plotx,ploty,ploty,1);	/* ia(t) */  
			ploty=(int)((-w*wscale)+97);
			d2monoplot(plotx,ploty,ploty,1);	/* w(t) */
				
			nc=nc+h;
		}	
		close(fd);						
		getch();

return 0;
}
