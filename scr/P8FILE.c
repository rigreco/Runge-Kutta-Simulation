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

extern int fd; /* x FILE LOW lEVEL DON'T FORGET THIS */ 

/* LOCAL GLOBAL */ 

char *FILE_NAME1="rcrk";
char *FILE_NAME2="dcrk"; 

/* pointing to unused memory at 4192 for a buffer 
   if this gives problems change to something else */ 
struct fileinfo *fi = (struct fileinfo *)4192; 

int p8create(name, maintype, subtype ) 
char *name; 
unsigned maintype,subtype; 
{ 
    int fh; 

    /* overwrite file if it already exists - set all access */ 
    if((fh=open(name, O_WRONLY|O_TRUNC|O_CREAT,0xc3)) == -1) return fh; 
    /* close it and get prodos to change the filetype for you */ 
    close(fh); 

    /* get the fileinfo from ProDOS */ 
    if (getfinfo (name, fi) == -1) { 
        return -2; 
     } 

    /* set the file info to whatever you wish - 
       you can set other info as well using this call sequence */ 
 fi->file_type = (unsigned char)maintype; 
 fi->aux_type = subtype; 
 setfinfo(name,fi); 

    /* open the file again */ 
 fh=open(name, O_WRONLY,0xc3); 
 /* return the open handle */ 
 return fh; 
} 

ovmain(filename) 
unsigned filename;
{ 

switch(filename)
       {
       case 1:
                     	 /* create or or owerwrite output file BIN format */ 
                		 fd=p8create(FILE_NAME1,6,0); 
						 break;
       case 2:			 
	   					 /* create or or owerwrite output file BIN format */ 
                		 fd=p8create(FILE_NAME2,6,0); 
       }
                                 
                if (fd == -1) 
                   { if (errno == EACCES)
						   {
			               puts("unable to access file");
			               getch();
			               /*_exit();*/
						   }
			               else if (errno == ENOENT) 
						   {
						   puts("unable to open file");
						   getch();
			               /*_exit();*/
			               }
			               else 
						   {
						   puts("open error number");
						   puts(errno);
						   getch();
			               /*_exit();*/
			               }
                   } 
                 else if (fd==-2) 
                           { puts("do not get fileinfo"); 
                           } 
               close(fd);             
           
        /*getch(); */
        return 0; 
} 

