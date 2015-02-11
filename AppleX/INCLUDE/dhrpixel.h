/* structure used by Double Hi-Res 140 x 192 x 16 color plot routines */
/* by Bill Buckels 2013 */

/* note: if this structure is expanded, the G2 global library structure in
         dhrpixel.c must be expanded to match and a new library must be
         built and put into the lib directory. Also review the other
         library routines that use this structure to ensure they do not break. */

struct dhrpixel
{
	int pattern;	/* 7 positions 0 - 6 of 4 bit color straddling 4 7-bit bytes */
	int xaux;       /* offset for auxmem pointer address */
	int xmain;      /* offset for mainmem pointer address */

	unsigned char caux;   /* auxmem color bitmap */
	unsigned char cmain;  /* mainmem color bitmap */
	unsigned char mska;   /* auxmem mask to erase old color */
	unsigned char mskm;   /* mainmem mask to erase old color */

};

