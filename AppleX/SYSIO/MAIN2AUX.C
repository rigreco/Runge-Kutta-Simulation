/* move a block of data from main to auxiliary memory */
/* do an absolute ml call */

#define A1L  0x3c
#define A1H  0x3d
#define A2L  0x3e
#define A2H  0x3f
#define A4L  0x42
#define A4H  0x43

maintoaux(src1,src2,dest)
unsigned int src1,src2,dest;
{

    /* load the registers and do the call */
    unsigned char *ptr=(unsigned char *)A1L;

    *ptr++=(unsigned char)(src1&0xff);
    *ptr++=(unsigned char)(src1>>8);
    *ptr++=(unsigned char)(src2&0xff);
    *ptr  =(unsigned char)(src2>>8);

     ptr=(unsigned char *)A4L;
     *ptr++=(unsigned char)(dest&0xff);
     *ptr  =(unsigned char)(dest>>8);
#asm
    sec
    jsr  $c311
#endasm

}

