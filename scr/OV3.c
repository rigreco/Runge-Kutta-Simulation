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
extern int cnt,fd,z; /* x FILE LOW lEVEL DON'T FORGET THIS */ 
extern struct data {
					char v[20];
					char i[20];
					char ideal[20];
					};

/* LOCAL GLOBAL */
char *FILE_NAME="rcrk";

ovmain()
{

double nc,vr,ir,exa,xscale,iscale,vscale;
int plotx,ploty,plotey,ic,px,py;
struct data rk;
double atof(); /* DON'T FORGET THIS */
char tx[4];
	/* inizialization */
	
	px=(int)0.0;
    py=(int)0.0;
	ic=(int)0.0;
	xscale=(double)100.0;  /* set x scale plot */
	iscale=(double)2500.0;	/* set y (i(t)) scale plot */
	vscale=(double)1.0;	/* set y (vc(t)) scale plot */
	nc=(double)0.0;	
		
							
		/* GRAPHICS SECTION */		
					
		/* Axes */ 
		for (px=0,py=96;px<=560;++px)
		{
			d2monoplot(px,py,py,1);
			/*d2monoplot(px,py-sur,py-sur,2); /* final voltage value E */ 
		}  /*Axis X */
		
		/*			
		for (px=0,py=0;py<=192;++py)
		{
			d2monoplot(px,py,py,1);
		} /* Axis Y */
		
		/* labels */
		monoplots("t=",505,36,1,'M');
		monoplots("v(t)=",25,0,1,'M');
		monoplots("i(t)=",25,10,1,'M');
						
		/* read first recort (header) for increment file pointr */
		open(FILE_NAME,O_RDONLY,0xC3);
		read(fd,fbuf,80);
			
		/* Main Plot */
		for (ic=0;ic<cnt;ic++)
		{
			/* read data fromfile */
			read(fd,rk.v,20); /* read vc(t) */
			read(fd,rk.i,20); /* read i(t) */
			read(fd,rk.ideal,20); /* read exact vc(t) */
			
			/* save data in doubles */
			vr=(double)atof(rk.v);
			ir=(double)atof(rk.i);
			exa=(double)atof(rk.ideal);
		    
		    /* presentation data*/
			monoplots(rk.v,110,0,1,'M');
			monoplots(rk.i,110,10,1,'M');
			ftoa(nc,tx,2,1);
			monoplots(tx,535,36,1,'M');
		
			/* plot graph of data*/
			plotx=(int)((nc*xscale)+1);
			ploty=(int)((-vr*vscale)+95);
			d2monoplot(plotx,ploty,ploty,1);	/* vc(t) */  
			ploty=(int)((-ir*iscale)+97);
			d2monoplot(plotx,ploty,ploty,1);	/* i(t) */
		if (z)	{
		
			plotey=(int)((-exa*vscale)+95);
			d2monoplot(plotx,plotey,plotey,1);		/* plot charge exact solution in double pixel */
			d2monoplot(plotx+1,plotey,plotey,1); 
		}
		/*  if (chk=1)
		  {	  
		  	plotey=(int)(-exact(nc)+95);     /* Exact solution in charge 
		  }
			else 
			{
				plotey=(int)(-exact2(nc,keep)+95); /* Exact solution in discharge 
	    	}
		
			d2monoplot(plotx,plotey,plotey,1);		/* plot charge exact solution in double pixel 
			d2monoplot(plotx+1,plotey,plotey,1); 
		*/	
			nc=nc+h;
		}	
		close(fd);						
		getch();

return 0;
}
