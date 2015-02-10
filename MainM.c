/* Copyright (C) 2013 Riccardo Greco rigreco.grc@gmail.com.
*   
*  This work is based on 1999-2000 Thesis work of Greco Riccardo.
*  It implement an Runge Kutta 4(5)^ order integration numerical method of differential equations set
*  by use of double precision floating point operation in Aztec C65 language.
*  It allow to simulate different mathematical models such as:
*  Resistance Capacitor electrical circuit, Direct Current electric motor,
*  Alternative Current three phase induction motor.
*   
*/
#include <stdio.h>

char *title = "RK Simulation";
char *title1= "Version 1.1";
char *title2= "Main Menu";
char *title3= "______________________________________________________________________________";
char *title4= "by Greco Riccardo for Apple II in Aztec C";

ovmain()
{
char rev;
	/* set screen */        
		#asm
      		jsr $c300
    	#endasm
    
	
	/* Presentation */
    scr_curs(1,1);
	puts(title);
	scr_curs(1,69);
	puts(title2);
	scr_curs(2,1);
    puts(title1);
    scr_curs(3,1);
    puts(title3);
    scr_curs(5,30);
    puts("Work on Models");
    scr_curs(7,30);
    puts("1.  RC Electric Circuit");
    scr_curs(8,30);
    puts("2.  DC Electric Motor");
    scr_curs(9,30);
    puts("3.  AC 3P Electric Motor");
    scr_curs(10,30);
    puts("4.  Custom y'(x)=f(x,y(x))");
    scr_curs(12,30);
    puts("Advanced Operations");
    scr_curs(14,30);
    puts("5.  Output to formatted file");
    scr_curs(15,30);
    puts("6.  Save graph to file");
    scr_curs(17,30);
    puts("0.  EXIT");
    
    scr_curs(19,1);
    puts("Type the number.");
	
	scr_curs(21,1);
	puts(title3);
	scr_curs(22,1);
	puts(title4);

IN:	scr_curs(19,17);
	rev=getch();

    switch (rev){
    case '1': 
		return 1;
		break;
	case '2':
		return 2;
		break;
	case '3':
		return 3;
		break;
	case '4':
		return 4;
		break;
	case '5':
		return 5;
		break;
	case '6':
		return 6;
		break;	
	case '0':
		return 0;
		break;
	default:
		goto IN;
	}
return 0;
}
