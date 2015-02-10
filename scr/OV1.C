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
/* INPUT MODULE */
#include <math.h>
#include <stdio.h>
#define micro 1.0e-6
#define kilo 1.0e+3

/* GENERAL GLOBAL */
extern double  h,time,time2,sur,r,c,tau,yinit;
extern char fbuf[80];
extern int cnt,z;

/* LOCAL GLOBAL */
char *title = "Runge Kutta and Runge Kutta Fehlberg integration methods";
char *title1= "R-C circuit transient state simulation:";
char *title2= "charge:    [vc'(t)=(1/RC)*(E-vc(t))]- [i(t)=(E-vc(t))/R]";
char *title3= "discharge: [vc'(t)=(1/RC)*(-vc(t))] - [i(t)=(-vc(t))/R]"; 
char *title4= "in Aztec C for Apple II 128k series - by Greco Riccardo - Apple ][ Forever!";
char *title5= "Thanks to Bill Buckels for all support - http://www.aztecmuseum.ca/ ";

char *out[8]={" RCCircuit h="," ts="," td="," E="," R="," C="," vc(0)="," cycles="}; /* always at global */

ovmain()
{
char buf[20],conv[4],rev;
double atof(); /* DON'T FORGET THIS */

IN:		/* set screen */        
		#asm
      		jsr $c300
    	#endasm
	    	
    	buf[0]='\0';      	/* buffers reset */
		fbuf[0]='\0';
		   
    	/* Presentation */
        puts(title);
        puts(title1);
        puts(title2);
        puts(title3);
        puts(title4);
        puts(title5);
        puts(" ");
          
	    /* Input data */
		do{
		puts("Time step integration (Def. 0.01s) h [s] -> ");
		h=(double)atof(gets(buf));
		} while (h<0 || h<=0.005);
		
		strcat(fbuf,out[0]);
		strcat(fbuf,buf);
		
		do{
		puts("Time simulation charge (Def. 5) ts [s] -> ");
		time=(double)atof(gets(buf));
		} while (time<0);
		
		strcat(fbuf,out[1]);
		strcat(fbuf,buf);
	    
		do{
		puts("Istant time to start discharge (Def. 2.5) (td<=ts) td [s] ->"); 	/* td istant time to discarge */
		time2=(double)atof(gets(buf));
		} while (time2<0 || time2>time);
		
		strcat(fbuf,out[2]);
		strcat(fbuf,buf);
	
		puts("Input Voltage value (Def. 50) E [Volt] -> "); 					/* Input step voltage E [V] */
		sur=(double)atof(gets(buf));
		
		strcat(fbuf,out[3]);
		strcat(fbuf,buf);
		
		do{
		puts("Resistence value (Def. 10) R [KiloOhm]-> "); 						/* Resistence R */
		r=(double)atof(gets(buf));
		} while (r<=0);
		
		r=(double)(r*(kilo));									/* converting in Farad from here to the end */
		ftoa(r,buf,6,1);
				
		strcat(fbuf,out[4]);
		strcat(fbuf,buf);
				 
		do{
		puts("Capacity value (Def. 20) C [micoFarad] -> "); 					/* Capacity C */
		c=(double)atof(gets(buf));				
		} while (c<=0);
		
		c=(double)(c*(micro));									/* converting in Farad from here to the end */
		ftoa(c,buf,6,1);   										/* new value of c in buf (only for show)*/
		
		strcat(fbuf,out[5]);
		strcat(fbuf,buf);
		
		puts("Initial charge condition (Def. 0) (@t=0s) vc(0) [Volt] -> ");	/* Iniztial charge condition vc(0) */  
		yinit=(double)atof(gets(buf));
		
		strcat(fbuf,out[6]);
		strcat(fbuf,buf);
	    
	    /* calc and set parameters */	
		tau=(double)(r*c);											/* Tau=R*C  R [Ohm] C [Farad]*/
		/*cnt=(int)(time/h);*/
		
	    strcat(fbuf,out[7]);
		ftoa((time/h),buf,0,1);										/* 0 decimal like int */
		strncpy(conv,buf,4);										/* save cnt to conv first 4 digit*/
		strcat(fbuf,buf);
		
		puts(fbuf); /* Input data Review */
		
		puts("Do you want to review input data (Y/N)?");
		rev=getch();
if (rev == 'Y' || rev == 'y') goto IN;		
    	
		/* reset buffers */ 
		fbuf[0]='\0'; 
		buf[0]='\0';
		
		/* set screen */
		scr_clear();
    	scr_curs(0,0);
				
		/* Simulation data review */
		puts("Simulation parameters set:");
		scr_curs(2,0);				
		puts("Number of input cycles:");
		scr_curs(2,31);
		puts(conv);
		puts("Input voltage E=");
		scr_curs(3,31);
		puts(ftoa(sur,buf,4,1)); 									/* 14 digits in double precision */
		scr_curs(3,50);
		puts("V");
		puts("Init value vc(0)=");
		scr_curs(4,31);
		puts(ftoa(yinit,buf,4,1));
		scr_curs(4,50);
		puts("V");
		puts("Circuit time constant Tau=R*C=");
		scr_curs(5,31);
		puts(ftoa(tau,buf,14,1));
		scr_curs(5,50);
		puts("s");
		puts("Time step integration h=");
		scr_curs(6,31);
		puts(ftoa(h,buf,6,1));
		scr_curs(6,50);
		puts("s");
		puts("Time simulation ts = ");
		scr_curs(7,31);
		puts(ftoa(time,buf,4,1));
		scr_curs(7,50);
		puts("s");
		puts("");
		
		puts("Do you want to plot exact solution too (Y/N)?");
		rev=getch();
		if (rev == 'Y' || rev == 'y') z=1;
		
		rev='1';
		puts("Select the method [1]= RK4 - [2]= RKF(4)5");
		rev=getch();
		/*puts("Press any key to start simulation...");
		getch();*/
		if (rev=='2') return 2;
		else return 1;
		
				
	return 0;
}

