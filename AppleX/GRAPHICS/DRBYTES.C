/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : drbytes.c
Description  : G2 Library Routine
               Double Hi-Res 140 x 192 x 16 color array
Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */
/*

The following is logically reordered to match the lores
color order...

                                                Repeated
                                                Binary
          Color         aux1  main1 aux2  main2 Pattern
          Black          00    00    00    00    0000
          Magenta        08    11    22    44    0001
		  Dark Blue      11    22    44    08    1000
          Violet         19    33    66    4C    1001
          Dark Green     22    44    08    11    0100
          Grey1          2A    55    2A    55    0101
          Medium Blue    33    66    4C    19    1100
          Light Blue     3B    77    6E    5D    1101
          Brown          44    08    11    22    0010
          Orange         4C    19    33    66    0011
          Grey2          55    2A    55    2A    1010
          Pink           5D    3B    77    6E    1011
          Green          66    4C    19    33    0110
          Yellow         6E    5D    3B    77    0111
          Aqua           77    6E    5D    3B    1110
          White          7F    7F    7F    7F    1111

*/

/*

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

*/

/* the following array is based on the above */
unsigned char dhrbytes[16][4] = {
	0x00,0x00,0x00,0x00,
	0x08,0x11,0x22,0x44,
	0x11,0x22,0x44,0x08,
	0x19,0x33,0x66,0x4C,
	0x22,0x44,0x08,0x11,
	0x2A,0x55,0x2A,0x55,
	0x33,0x66,0x4C,0x19,
	0x3B,0x77,0x6E,0x5D,
	0x44,0x08,0x11,0x22,
	0x4C,0x19,0x33,0x66,
	0x55,0x2A,0x55,0x2A,
	0x5D,0x3B,0x77,0x6E,
	0x66,0x4C,0x19,0x33,
	0x6E,0x5D,0x3B,0x77,
	0x77,0x6E,0x5D,0x3B,
	0x7F,0x7F,0x7F,0x7F};

/* position of pixels in 4 byte pattern */
/* remember that byte 0 and byte 2 are auxmem
   and byte 1 and byte 3 are main mem
   and the 4 bit pattern of the 7 pixels straddle
   the two memory banks */

/* 7 pixels = 4 bytes */

/* left for reference...
unsigned char dhrpattern[7][4] = {
0,0,0,0,
0,0,0,1,
1,1,1,1,
1,1,2,2,
2,2,2,2,
2,3,3,3,
3,3,3,3};

*/

/* mask values to erase previous contents of pixels */
/* for reference

unsigned char dhrmsk[7][2] = {
0x70, 0,
0x0f, 0x7e,
0x61, 0,
0x1f, 0x7c,
0x43, 0,
0x3f, 0x78,
0x07, 0};

*/

/* getpixel mask values - what color to use */
/* for reference

unsigned char dhrgetmsk[7][2] = {
0x0f, 0,
0x70, 0x01,
0x1e, 0,
0x60, 0x03,
0x3c, 0,
0x40, 0x07,
0x78, 0};

*/


/* offset into base of memory frame "raster" of byte pairs for pixels */
/* double hi-res xbase */
/* for reference

char DHB[140] = {
0,0,0,0,0,0,0,
2,2,2,2,2,2,2,
4,4,4,4,4,4,4,
6,6,6,6,6,6,6,
8,8,8,8,8,8,8,
10,10,10,10,10,10,10,
12,12,12,12,12,12,12,
14,14,14,14,14,14,14,
16,16,16,16,16,16,16,
18,18,18,18,18,18,18,
20,20,20,20,20,20,20,
22,22,22,22,22,22,22,
24,24,24,24,24,24,24,
26,26,26,26,26,26,26,
28,28,28,28,28,28,28,
30,30,30,30,30,30,30,
32,32,32,32,32,32,32,
34,34,34,34,34,34,34,
36,36,36,36,36,36,36,
38,38,38,38,38,38,38};

*/

