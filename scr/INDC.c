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


/* GENERAL GLOBAL */
extern double  h,time;
extern char fbuf[80];
extern int cnt;

/* LOCAL GLOBAL */
char *title = "Runge Kutta Fehlberg integration methods";
char *title1= "DC Motor transient state simulation:";
char *title2= "Current:      [ia'(t)=(va/la)-(ra/la)*ia(t)-kf*w(t)/la]";
char *title3= "Anglar speed: [w'(t)=(1/j)*(MM-MC)=(1/j)*(kf*ia(t)-MC)]"; 
char *title4= "in Aztec C for Apple II 128k series - by Greco Riccardo - Apple ][ Forever!";
char *title5= "Thanks to Bill Buckels for all support - http://www.aztecmuseum.ca/ ";

char *out[3]={" DCMotor h="," ts="," cycles="}; /* always at global */

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
		} while (h<0 || h<=0.005 || h>0.01);
		
		strcat(fbuf,out[0]);
		strcat(fbuf,buf);
		
		do{
		puts("Time simulation (Def. 5) ts [s] -> ");
		time=(double)atof(gets(buf));
		} while (time<0);
		
		strcat(fbuf,out[1]);
		strcat(fbuf,buf);
	    		
	    strcat(fbuf,out[2]);
		ftoa((time/h),buf,0,1);										/* 0 decimal like int */
		strncpy(conv,buf,4);										/* save cnt to conv first 4 digit*/
		strcat(fbuf,buf);
		
		puts(fbuf); /* Input data Review */
		
		puts("Do you want to review input data (Y/N)?");
		rev=getch();
if (rev == 'Y' || rev == 'y') goto IN;		
    	
		/* set screen */
		scr_clear();
    	scr_curs(0,0);
				
		/* Simulation data review */
		puts("DC Motor Default parameters set:");
		scr_curs(2,0);				
		puts("Number of input cycles:");
		scr_curs(2,31);
		puts(conv);
		puts("Input voltage E= 160.0 V");
		puts("Armor (stator) resistence ra= 9.47 Ohm");
		puts("Armor (stator) inductance la= 0.0375 Henry");
		puts("Flux gain (kf=k*flux) kf= 0.98 Wb");
		puts("Rotor inertia j= 0.011 kg*m2");
		puts("Load torque MC= 0.0 kg*m");
	
		puts("");
	
		puts("Press any key to start simulation...");
		getch();
		
				
	return 0;
}

