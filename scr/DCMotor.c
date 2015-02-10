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
/* PROCESS MODULE */
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

#define rkfr 1.0e-3		/* RKF max resolution h<rk4r */


/* GENERAL GLOBAL */
extern double h,time;
extern char fbuf[80];
extern int cnt,fd;	
extern struct data {
				char v[20];
				char i[20];
				/*char ideal[20];*/
			};

/* LOCAL GLOBAL */
char *outr[4]={"t=","    ia(t)=","     w(t)="};
char *FILE_NAME="dcrk";
/*double MC,va,ra,kf,l,j;


/*Fehlberg parameters */
double acca[5]={1.0/4.0,3.0/8.0,12.0/13.0,1.0,1.0/2.0};
double erre1[5]={1.0/4.0,0.0,0.0,0.0,0.0};
double erre2[5]={3.0/32.0,9.0/32.0,0.0,0.0,0.0};
double erre3[5]={1932.0/2197.0,-7200.0/2197.0,7296.0/2197.0,0.0,0.0};
double erre4[5]={439.0/216.0,-8.0,3680.0/513.0,-845.0/4104.0,0.0};
double erre5[5]={-8.0/27.0,2.0,-3544.0/2565.0,1859.0/4104.0,-11.0/40.0};

double erre[5]={1.0/360.0,-128.0/4275.0,-2197.0/75240.0,1.0/50.0,2.0/55.0};

double ips5[5]={25.0/216.0,0.0,1408.0/2565.0,2197.0/4104.0,-1.0/5.0};
/*double ips6[6]={16.0/135.0,0.0,6656.0/12825.0,28561.0/56430.0,-9.0/50.0,2.0/55.0};*/


/* Integrated equation sets */ 
int funrk(x,ya,eq)
double x,ya[2],eq[2];
{
	double va,ra,kf,la,j,MC;
	/*ya[0]=y3=ia(t) ya[1]=y4=w(t) variables array /*
		
    /* ***** TEST equations WORK *******
	eq[0]=ya[0]+2*ya[1];
    eq[1]=10.0-ya[0];
    /* Harmonic oscillator (change initial condition) 
    eq[0]=-2*ya[1];
    eq[1]=ya[0];*/
  
  /* DATA MOTOR */
  va=(double)160.0;     
  ra=(double)9.47;
  kf=(double)0.98;     /* kf=k*fi */
  la=(double)0.0375;
  j=(double)0.011;
  MC=(double)0.0;  /*4.2*/    
  
  /* DC Motor equations */  
    eq[0]=(va/la)-(ra/la)*ya[0]-(kf*ya[1])/la;	/* ia'(t)=(va/la)-(ra/la)*ia(t)-kf*w(t)/la */
    eq[1]=(kf*ya[0]-MC)/j;						/* w'(t)=(1/j)*(MM-MC)=(1/j)*(kf*ia(t)-MC) */
        
  /*
    eq[0]=42666.6-2525.3*ya[0]-261.3*ya[1];      
    eq[1]=89.0*ya[0]-381.8;	*/				
}													


/*RKF45 Module */
int runge_kutta(x,h,y_init,y)
double x,h,y_init[2],y[2];
{
    double r11,r21,r31,r41,r51,r61,r12,r22,r32,r42,r52,r62,ya[2],eq[2]; /*,err*/

    /* RK inizialization */
    y[0]=(double)0.0;    /* y3[0]=ia(t) return integrated value */
    y[1]=(double)0.0;      /* y4[0]=w(t)  return integrated value */
    eq[0]=(double)0.0;
    eq[1]=(double)0.0;
    ya[0]=y_init[0];				/* VIP */
    ya[1]=y_init[1];
    /*err=(double)0.0;*/
    
  
   /*
	do
    {	
	 
	 /* 1^ order */
	 funrk(x,ya,eq);		
	 r11=eq[0];
	 r12=eq[1];
	 
	 /* 2^ order */
	 ya[0]=(double)(y_init[0]+erre1[0]*r11*h);
	 ya[1]=(double)(y_init[1]+erre1[0]*r12*h); 
	 
	 funrk(x+acca[0]*h,ya,eq);
	 											
	 r21=eq[0];
	 r22=eq[1];
	 
	 /* 3^ order */
	 ya[0]=(double)(y_init[0]+erre2[0]*r11*h+erre2[1]*r21*h);
	 ya[1]=(double)(y_init[1]+erre2[0]*r12*h+erre2[1]*r22*h);
	 
	 funrk(x+acca[1]*h,ya,eq);								
	 
	 r31=eq[0];
	 r32=eq[1];
	 
	 /* 4^ order */
	 ya[0]=(double)(y_init[0]+erre3[0]*r11*h+erre3[1]*r21*h+erre3[2]*r31*h);
	 ya[1]=(double)(y_init[1]+erre3[0]*r12*h+erre3[1]*r22*h+erre3[2]*r32*h);
	 
	 funrk(x+acca[2]*h,ya,eq);				
	 r41=eq[0];
	 r42=eq[1];
	 
	 /* 5^ order */
	 ya[0]=(double)(y_init[0]+erre4[0]*r11*h+erre4[1]*r21*h+erre4[2]*r31*h+erre4[3]*r41*h);
	 ya[1]=(double)(y_init[1]+erre4[0]*r12*h+erre4[1]*r22*h+erre4[2]*r32*h+erre4[3]*r42*h);
	 
	 funrk(x+acca[3]*h,ya,eq);	
	 r51=eq[0];
	 r52=eq[1];
	 
	 /* 6^ order only for estimated error for adaptative step method 
	 ya[0]=(double)(y_init[0]+erre5[0]*r11*h+erre5[1]*r21*h+erre5[2]*r31*h+erre5[3]*r41*h+erre5[4]*r51*h);
	 ya[1]=(double)(y_init[1]+erre5[0]*r12*h+erre5[1]*r22*h+erre5[2]*r32*h+erre5[3]*r42*h+erre5[4]*r52*h);
	 
	 funrk(x+acca[4]*h,ya,eq); 
	 r61=eq[0];
	 r62=eq[1];
 	/*	
  	 err=(fabs(erre[0]*r11+erre[1]*r31+erre[2]*r41+erre[3]*r51+erre[4]*r61)*h);			/* estimate the error */
  /*	    
	 
	h=h/2; 
	 	 
  		   	
	}
    while (err>rkfr);
    */
	/* y3 y4 weighted average of operators 5^ order */
   		y[0]=(double)(y_init[0]+(ips5[0]*r11+ips5[2]*r31+ips5[3]*r41+ips5[4]*r51)*h);
	 	y[1]=(double)(y_init[1]+(ips5[0]*r12+ips5[2]*r32+ips5[3]*r42+ips5[4]*r52)*h);
	 
	   /* ------------------------------------------------------------------------------*/
     
}

ovmain()
{
char buf[20];
/*double atof(); /* DON'T FORGET THIS */
double x,y[2],y_init[2];
struct data rk;
		
	
       	/* inizialization */
        cnt= (int)0.0;		/* Reset counter */
		y[0] = (double)0.0;
		y[1] = (double)0.0;
		y_init[0]= (double)0.0; /* init value of current ia(t) (for Harmonic oscillator y_3=10.0) */
		y_init[1]= (double)0.0; /* init value of angular speed w(t) (for Harmonic oscillator y_4=10.0) */
        x=(double)0.0;  /* time in simulation */ 
    			
		/* Start simulation */
		scr_clear();
    	scr_curs(0,0);
		puts("Pocessing...");
				
		/* open and write header data to file */ 
		open(FILE_NAME,O_WRONLY|O_APPEND,0xC3);
		write(fd,fbuf,80);
		
		buf[0]='\0';      	/* buffers reset */
		fbuf[0]='\0';
		
		/* RK main Cycle */			
		while (x<time) {

        	   
			runge_kutta(x,h,y_init,y); /* call RKF45 process module */
			
									
			/* store output in buffer */
			ftoa(x,buf,6,2);
			strcat(fbuf,outr[0]);
			strcat(fbuf,buf);  /* store time (x) */
			
			ftoa(y[0],buf,6,2);
			strcat(fbuf,outr[1]);
			strcat(fbuf,buf);	/* store speed i(t) (y3) */
								
			ftoa(y[1],buf,6,2);
			strcat(fbuf,outr[2]);
			strcat(fbuf,buf);	/* store current w(t) (y4) */
			
			/* converting using max floating resolution */			
			ftoa(y[0],rk.i,14,1); 	/* ia(t) */
			ftoa(y[1],rk.v,14,1);		/* w(t)	 */
							
			
			puts(fbuf); /* output to screen */
			
			/* write data result to file */ 
        	write(fd,rk.i,20); /* write ia(t) */
			write(fd,rk.v,20); /* write w(t) */
			
						
			fbuf[0]='\0'; 	/* reset buffer */
			
			y_init[0]=y[0];			/* save the current value of y3=ia(t) as new init value y_3 for next RK process step */
			y_init[1]=y[1];			/* save the current value of y4=w(t) as new init value y_4 for next RK process step */
			x=x+h;			/* increment time in simulation */	
			cnt++;			/* renew counter */ 
			
		}
		close(fd);			/* close the data file */
	
				
		puts("Press any key to start plotting...");
		getch();	
		
	return 0;
}

