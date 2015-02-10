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
#define chk 1			/* set chk to 1 charge */
#define rkfr 1.0e-6		/* RKF max resolution h<rk4r */
/*#define hmax 0.25		/* need for adaptative step 
#define emax 20.0e-3
#define emin 10.0e-3*/

/* GENERAL GLOBAL */
extern double sur,r,c,tau,h,time,time2,yinit,keep;
extern char fbuf[80];
extern int cnt,fd;	
extern struct data {
				char v[20];
				char i[20];
				char ideal[20];
			};

/* LOCAL GLOBAL */
char *outr[4]={"t=","    vc(t)=","     vcerr(t)=","     i(t)="};
char *FILE_NAME="rcrk";
double swi;

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



/* Functions sets */
int funrk(x,y,frk)
double x,y,*frk;
{
	frk[0] = (double)(((sur*swi)-y)/tau);	/* RC Circuit Voltage frk[0]=vc'(t) Charge differential equation */
}													/* vc'(t)=(1/RC)*(E-vc(t)) charge*/
													/* vc'(t)=(1/RC)*(-vc(t)) discharge */
double current(v)
double(v);
{
	return(((sur*swi)-v)/r); /* i(t)=(E-vc(t))/R charge*/
}							 /* i(t)=(-vc(t))/R discharge */

double exact(x)
double(x);
{
	return (((yinit-sur)*exp(-x/tau))+sur); /* Exact solution charge vc(t)=(vc(0)-E)*exp(-t/RC)+E */
}									 

double exact2(x)
double (x);
{
	return (keep*exp(-x/tau));			/* Exact solution discharge vc(t)=(vc(td))*exp(-t/RC) */
}



/*RKF45 Module */
int runge_kutta(x,y,h,y3)
double x,y,h,*y3;
{
    double r1,r2,r3,r4,r5,r6,frk,err; /*sigma,div,div2;

    /* RK inizialization */
    y3[0] = (double)0.0;
    frk = (double)0.0;
    err=(double)0.0;
    
   /* do
    {
    
	 /* 1^ order */																						
	 funrk(x,y,&frk);		
	 r1=frk;
	 /* 2^ order */
	 funrk(x+acca[0]*h,(double)y+erre1[0]*r1*h,&frk);											
	 r2=frk;
	 /* 3^ order */
	 funrk(x+acca[1]*h,(double)y+erre2[0]*r1*h+erre2[1]*r2*h,&frk);							
	 r3=frk;
	 /* 4^ order */
	 funrk(x+acca[2]*h,(double)y+erre3[0]*r1*h+erre3[1]*r2*h+erre3[2]*r3*h,&frk);				
	 r4=frk;
	 /* 5^ order */
	 funrk(x+acca[3]*h,(double)y+erre4[0]*r1*h+erre4[1]*r2*h+erre4[2]*r3*h+erre4[3]*r4*h,&frk);		
	 r5=h*frk;
	 
	 /* 6^ order only for estimated error for adaptative step method 
	 funrk(x+acca[4]*h,(double)y+erre5[0]*r1*h+erre5[1]*r2*h+erre5[2]*r3*h+erre5[3]*r4*h+erre5[4]*r5*h,&frk);
	 r6=frk;
 		
  	 err=(fabs(erre[0]*r1+erre[1]*r3+erre[2]*r4+erre[3]*r5+erre[4]*r6)*h);			/* estimate the error 
  	 
	h=h/2; /*non adaptative*/ 
	   
	/* adaptative step integration  
	div=(double)(rk4r/err);
	div2=(double)pow(div,0.25);
  	sigma=(double)(0.84*div2);
  	 
	if (sigma<=0.1) 	h=0.1*h;
  	else if (sigma>=4) 	h=4*h;
	else 				h=sigma*h;
  	/* Alternative method 
	if (err>=emax) h=h/2;
	if (err<=emin) h=h*2;
		  				 
  	if (h>hmax) h=hmax;	*/			 
 /* 		   	
	}
    while (err>rkfr); 
   */ 
   
	/* y3 weighted average of operators 5^ order */
   	y3[0]=(double)(y+(ips5[0]*r1+ips5[2]*r3+ips5[3]*r4+ips5[4]*r5)*h);
}

ovmain()
{
char buf[20],rev;
double atof(); /* DON'T FORGET THIS */
double x,x2,nc,y3,y,errtx,cur,exa;
struct data rk;
		
	
       	/* inizialization */
        cnt=(int)0.0;		/* Reset counter */
		y3 = (double)0.0;
        x=(double)0.0;  /* time in simulation */ 
        x2=(double)0.0; /* time in discharge */
        keep=(double)0.0;
        
        swi=(double)1.0; 	/* switch set to 1 = charge */
       	y=yinit;			/* set initial condition parameter vc(o) */		
    	/*h=hmax;				/* need for adaptative step */
				
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

            runge_kutta(x,y,h,&y3);
			cur=current(y3);
			
			if (x <= time2)
			{
				exa=(double)exact(x);
				errtx=(double)fabs(y3-exa); 			/* exact solution in charge */
			}
			
			if (x > time2) 
			{
				if (chk) 
				{
					swi=(double)0.0;  /* switch set to 0 = discharge */
					keep=(double)y3;  /* keep the value of vc(td) in the istant of discharge  */
					!chk;			  /* NOT chk */
				}
					exa=(double)exact2(x2);
					errtx=(double)fabs(y3-exa);			/* exact solution in discharge */
					x2=x2+h;							/* increment time in discharge */
			}
			
						
			/* store output in buffer */
			ftoa(x,buf,6,2);
			strcat(fbuf,outr[0]);
			strcat(fbuf,buf);  /* store time (x) */
			
			ftoa(y3,buf,6,2);
			strcat(fbuf,outr[1]);
			strcat(fbuf,buf);	/* store voltage vc(t) (y3) */
			
			ftoa(errtx,buf,6,2);
			strcat(fbuf,outr[2]);
			strcat(fbuf,buf);	/* store voltage error vcerr(t) (errtx) */
			
			ftoa(cur,buf,6,2);
			strcat(fbuf,outr[3]);
			strcat(fbuf,buf);	/* store current i(t) (cur) */
			
			/* converting using max floating resolution */			
			ftoa(y3,rk.v,14,1); 	/* vc(t) */
			ftoa(cur,rk.i,14,1);	/* i(t)	 */
			ftoa(exa,rk.ideal,14,1);	/* vc(t) exact solution */						
			
			puts(fbuf); /* output to screen */
			
			/* write data result to file */ 
        	write(fd,rk.v,20); /* write vc(t) */
			write(fd,rk.i,20); /* write i(t) */
			write(fd,rk.ideal,20); /* write vc(t) exact solution */
						
			fbuf[0]='\0'; 	/* reset buffer */
			
			y=y3;				
			x=x+h;			/* increment time in simulation */	
			cnt++;			/* renew counter */ 
			
		}
		close(fd);			/* close the data file */
	
	/*printf("Cycles number= %d",(cnt-1)); /* NOT YET itoa ?*/ 
				
		puts("Press any key to start plotting...");
		getch();	
		
	return 0;
}

