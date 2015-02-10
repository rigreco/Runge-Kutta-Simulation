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
#include "d2monplt.h"
/*
extern int clearhgr();
*/
ovmain(screenmode)
unsigned screenmode;
{
       switch(screenmode)
       {
       case 1:
                     	 scr_clear();
						 d2hireson();
						 clearhgr(911);
						 maintoaux(0x4000,0x4000+8191,0x4000);
						 break;
       case 2:			 
	   					 d2hiresoff();
						 scr_clear();
       }
    return 0;
}
