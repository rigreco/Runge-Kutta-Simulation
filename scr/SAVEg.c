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

/* LOCAL GLOBAL */
char *FILE_Graph="Graph";

ovmain()
{
    scr_clear(); 
    scr_curs(0,0);
				 
 	/* bsave HGR2 */
	bsave(FILE_Graph);
	
	puts("Graph has been saved!");
	scr_curs(5,0);
	puts("Press any key ...");
	
	getch();
return 0;
}	
