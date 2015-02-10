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
#include <fcntl.h>
#include <errno.h>
#include <prodir.h> 

/* GENERAL GLOBAL */
extern double h,time;
extern char fbuf[80];
extern int cnt,fd,fd2; /* x FILE LOW lEVEL DON'T FORGET THIS */ 
extern struct data {
					char v[20];
					char i[20];
					char ideal[20];
					};

/* LOCAL GLOBAL */
char *outr1[4]={"  t="," vc(t)=","  i(t)=","  ve(t)="};
char *outr2[3]={"  t="," ia(t)=","  w(t)="};

char *FILE_OUT="rkout";
char *FILE_NAME1="rcrk";
char *FILE_NAME2="dcrk";

char *null="    ";

ovmain(outfile)
unsigned outfile;
{ 
char buf[20],fbuf2[30];
int ic; 
double nc;
struct data rk; 
			
			/* inizialization */	
            ic=(int)0.0; 
            nc=(double)0.0; 
            fbuf[0]='\0';
			fbuf2[0]='\0';
            buf[0]='\0'; 
                                          
    scr_clear(); 
    scr_curs(0,0);
			
	puts("Pocessing output file..."); 
    
				 /* open or overwrite output text file */
				fd2=open(FILE_OUT, O_WRONLY|O_TRUNC|O_CREAT,0xc3);
	
	switch(outfile)
       {
       case 1:			/***** RC *****/
                /* open and read header from process file rcrk*/ 
                fd=open(FILE_NAME1,O_RDONLY,0xC3); 
                read(fd,fbuf,80);  
				break;
       case 2:			/***** DC *****/	 
	   			/* open and read header from process file dcrk*/ 
                fd=open(FILE_NAME2,O_RDONLY,0xC3); 
                read(fd,fbuf,80);	   				
       }        
                                                                  
                /* open and write header to output file */ 
                open(FILE_OUT,O_WRONLY|O_APPEND,0xC3); 
                write(fd2,fbuf,80); 
                
                /* reset buffer */ 
               	fbuf[0]='\0';
               	fbuf2[0]='\0';
                buf[0]='\0'; 
               
         	         		
       
     switch(outfile)
       		{
			   case 1: 
							 for (ic=0;ic<cnt;ic++) 
                			{
							/***** RC *****/
                			/*store output in string buffer */ 
                			ftoa(nc,buf,6,1); 
               			 	strcat(fbuf,outr1[0]); 
               			 	strcat(fbuf,buf);  				/* store time (x) */ 
         
               				read(fd,rk.v,20); 				/* read vc(t) from process file */ 
                			read(fd,rk.i,20); 				/* write i(t) from process file */ 
                			read(fd,rk.ideal,20); 			/* read exact vce(t)*/
				/* chk 
                puts(rk.v); 
                puts(rk.i);         
                puts(rk.ideal);*/
                			strcat(fbuf,outr1[1]); 
                			strcat(fbuf,rk.v);  			/* store voltage vc(t) (rk.v) in string*/ 
                /*puts(fbuf);*/         
                			strcat(fbuf,outr1[2]); 
                			strcat(fbuf,rk.i);        		/* store current i(t) (rk.i) in string*/ 
                /*puts(fbuf);*/ 			
							strcat(fbuf2,outr1[3]); 
                			strcat(fbuf2,rk.ideal);        		/* store current ve(t) (rk.ideal) in string*/
				/*puts(fbuf);*/ 			
							strcat(fbuf2,null);				/* add null string to erase old */
							
							puts(fbuf);
							puts(fbuf2); 	          
                			write(fd2,fbuf,strlen(fbuf)); /* write string to out file */ 
                			write(fd2,fbuf2,strlen(fbuf2)); /* write string to out file */ 
							
							/* reset */                 
                			buf[0]='\0'; 
                			fbuf[0]='\0';
                			fbuf2[0]='\0';
                
							nc=nc+h;
							}
		       break;
							    
               case 2:
						 	for (ic=0;ic<cnt;ic++) 
                			{
							/***** DC *****/
							/*store output in string buffer */ 
                			ftoa(nc,buf,6,1); 
               			 	strcat(fbuf,outr2[0]); 
               			 	strcat(fbuf,buf);  				/* store time (x) */ 
         
               				read(fd,rk.v,20); 				/* read ia(t) from process file */ 
                			read(fd,rk.i,20); 				/* write w(t) from process file */ 
                		
                			strcat(fbuf,outr2[1]); 
                			strcat(fbuf,rk.v);  			/* store voltage ia(t) (rk.v) in string*/ 
                         
                			strcat(fbuf,outr2[2]); 
                			strcat(fbuf,rk.i);        		/* store current w(t) (rk.i) in string*/ 
                												
							strcat(fbuf,null);				/* add null string to erase old */
				   	   		
							puts(fbuf); /*chk */ 	          
                			write(fd2,fbuf,strlen(fbuf)); /* write string to out file */ 
                
							/* reset */                 
                			buf[0]='\0'; 
                			fbuf[0]='\0'; 
                
							nc=nc+h; 	     
							}
           }        	
    close(fd);
	close(fd2);           
		
	puts("Done!");
	puts("Press any key ...");
	getch();
	
	return 0;
}
