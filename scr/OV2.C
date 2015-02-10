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
#define rk4r 5.0e-3		/* RK4 max resolution h<rk4r */

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

/*RK4 Module */
int runge_kutta(x,y,h,y3)
double x,y,h,*y3;
{
    double r1,r2,r3,r4,r5,h1,err,y3err,y3div,frk,frkerr;

    /* RK inizialization */
    y3[0] = (double)0.0;
    y3err = (double)2.0;
    y3div = (double)6.0;
    frk = (double)0.0;
    frkerr = (double)0.5;
    err=(double)0.0;

    do
    {
        h1=(double)0.5*h;

        funrk(x,y,&frk);						/* 1^ order */
        r1=h*frk;

        funrk(x+h1,(double)y+frkerr*r1,&frk);	/* 2^ order */
        r2=h*frk;

        funrk(x+h1,(double)y+frkerr+r2,&frk);	/* 3^ order */
        r3=h*frk;

        funrk(x+h,(double)y+r3,&frk);			/* 4^ order */
        r4=h*frk;

        funrk(x+h,(double)y+r4,&frk);			/* 5^ order */
        r5=h*frk;

        err=fabs(r4-r5);						/* etimate the error */
        
        h=h/2;
        
    }
    while (err>rk4r); 							/* RK4 max resolution */

    /* y3 plus weighted average of operators 4^ order */
    y3[0] = (double)(y+(r1+y3err*r2+y3err*r3+r4)/y3div);

}

ovmain()
{
char buf[20],rev;/*conv[4]*/
double atof(); /* DON'T FORGET THIS */
double x,x2,nc,y3,y,errtx,cur,exa;
struct data rk;
		
		
       	/* inizialization */
        cnt=(int)0.0;		/* Reset counter */
		y3 = (double)0.0;
        x=(double)0.0;  /* time simulation */ 
        x2=(double)0.0; /* time discharge */
        keep=(double)0.0;
        
        swi=(double)1.0; 	/* switch set to 1 = charge */
       	y=yinit;			/* set initial condition parameter vc(o) */		
    			
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
					keep=(double)y3;          /* keep the value of vc(td) in the istant of discharge */ 
					!chk;			  /* NOT chk */	
				}
					exa=(double)exact2(x2);
					errtx=(double)fabs(y3-exa);	/* exact solution in discharge */
					x2=x2+h;
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
			x=x+h;
			cnt++;			/* renew counter */ 
			
		}
		close(fd);			/* close the data file */
	
	/*printf("Cycles number= %d",(cnt-1)); /* NOT YET itoa ? */	
	
		
		puts("Press any key to start plotting...");
		getch();	
		
	return 0;
}

