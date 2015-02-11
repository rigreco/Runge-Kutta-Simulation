#ifndef _G3H_
#define _G3H_

#define PAGEONE   poke(49236,0)
#define PAGETWO   poke(49237,0)

/*
          80STORE    off    $C000             49152,0
                     on     $C001             49153,0

*/

#define EIGHTYON  poke(49153,0)
#define EIGHTYOFF poke(49152,0)

#define TEXTMODE  0
#define LORES     1
#define GRAFMODE  2  /* graphics only */
#define DHRMODE   3  /* double hi-res graphics */
#define DLORES    4  /* double lo-res graphics */
#define TEXT80    5  /* 80 column textmode */
#define MIXEDMODE 6
#define FULLMODE  7


/*

color definitions for lores mode

black    COLOR=0
red      COLOR=1
dk blue  COLOR=2
purple   COLOR=3
dk green COLOR=4
gray     COLOR=5
med blue COLOR=6
lt blue  COLOR=7
brown    COLOR=8
orange   COLOR=9
grey     COLOR=10
pink     COLOR=11
lt green COLOR=12
yellow   COLOR=13
aqua     COLOR=14
white    COLOR=15

*/


#define LOBLACK   	0
#define LORED     	1
#define LODKBLUE 	2
#define LOPURPLE  	3
#define LODKGREEN	4
#define LOGRAY    	5
#define LOMEDBLUE	6
#define LOLTBLUE 	7
#define LOBROWN   	8
#define LOORANGE  	9
#define LOGREY    	10
#define LOPINK    	11
#define LOLTGREEN	12
#define LOYELLOW  	13
#define LOAQUA    	14
#define LOWHITE   	15


/*

 black    HCOLOR=0
 green    HCOLOR=1
 purple   HCOLOR=2
 white    HCOLOR=3
 black2   HCOLOR=4
 orange   HCOLOR=5
 blue     HCOLOR=6
 white2   HCOLOR=7

*/


/* timing loop function for slideshow - see G2 library function dwait.c */
#define XTIME 1024L
#define YTIME 32L



#endif