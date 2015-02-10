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
#include <stdio.h>


/* GENERAL GLOBAL */ 

double  h,time,time2,sur,r,c,tau,yinit,keep;
char fbuf[80];
int cnt,fd,fd2,z;
struct data {
				char v[20];
				char i[20];
				char ideal[20];
			};

int clearhgr(i)
int i;
{
   
/* Funzioni globali devono essere in modulo principale per essere condivisi
tra sovrapposizioni */
if (i!=911)
 {return 0;}
maintoaux (0,0,0);
black();
hgr();
   
}

main()
{
int a,b,c;
	z=0;
	b=0;
	c=0;
clearhgr(0);
IN:	
	a=ovloader("mainm");
	switch (a){
	case 0:
		_exit();
		break;
	case 1:
		b=ovloader("ov1"); /* input module */
		if (b==2) {
			ovloader("p8file",1); /* create or owerwrite work file */
			ovloader("ov2f"); /* process module by RKF45*/
    	}
    	else {
    		ovloader("p8file",1); /* create or owerwrite work file rcrk*/
    		ovloader("ov2"); /* process module by RK4*/
		}
		ovloader("ginit",1); /* open graph mode */
		ovloader("ov3"); /*output module */
		ovloader("ginit",2); /* close graph mode */
		break;
	case 2:
		ovloader("indc");
		ovloader("p8file",2); /* create or owerwrite work file dcrk*/
		ovloader("dcmotor");
		ovloader("ginit",1); /* open graph mode */
		ovloader("outdc");   /*output module */
		ovloader("ginit",2); /* close graph mode */
		c=1;
		break;
	case 5:
		if(b==1 || b==2){
		ovloader("outf",1);} /* create output file from rcrk */
		else if(c==1){
		ovloader("outf",2);} /* create output file from dcrk */
		break;
	case 6:
		ovloader("saveg");
		break;
	default:
		break;	
	}
goto IN;	
	
}

