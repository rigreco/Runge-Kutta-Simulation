#define PAGE2 ((char *)0x4000)
static int ysum, xoff, bitoff, point, point1;

static int
whpnt()
{
	if (bitoff!=6){
		point=3<<bitoff;
		point1=0;
	} else if (xoff != 39){
		point=0x40;
		point1=1;
	} else {
		point = 0x60;
		point1=0;
	}
}

static int
pnt(evencol,bit7)
register int evencol, bit7;
{
	int base;

	if (evencol)
		base=(xoff&1?2:1);
	else
		base=(xoff&1?1:2);

	point=bit7|base<<(bitoff&6);
	point1=0;

	if (bitoff==6)
		if (evencol)
			if (xoff&1) /*point 6 in odd bytes */
				point = bit7|0x20;
			else  /* point 6 in even bytes */
				point1=bit7;
		else
			if (xoff&1) {
				if (xoff != 0x27) /* if last point on line is red, don't */
					point1=bit7;   /* turn on bit 7 of next byte */
			} else
				point = bit7|0x20;
}

static int
complot(x,y,func, evencol,bit7)
register int x,y;
int (*func)(), evencol,bit7;
{
	int y1,y2,y3;

	if(y<64)
		y1=0;
	else if (y<128)
		y1=0x28;
	else
		y1=0x50;
	y2=(y&7)<<10;
	y3=(y&0x38)<<4;
	ysum=y1+y2+y3;

	xoff=x/7;
	bitoff=x%7;

	(*func)(evencol, bit7); /*compute point & point1 */

#ifdef DEBUG
	printf("\n\ty1=%x, y2=%x, y3=%x\n",y1,y2,y3);
	printf("\txoff=%x,point=%x, point1=%x\n",xoff,point,point1);
#endif
    PAGE2[ysum+xoff] |= point;
    PAGE2[ysum+xoff+1] |= point1;
}

#define EVENCOL 1
#define ODDCOL 0

bplot(x,y)
{
	complot(x,y,pnt, EVENCOL, 0x80);
}

vplot(x,y)
{
	complot(x,y,pnt, EVENCOL, 0);
}

rplot(x,y)
{
	complot(x,y,pnt, ODDCOL, 0x80);
}

gplot(x,y)
{
	complot(x,y,pnt, ODDCOL, 0);
}

plot(x,y)
{
	complot(x,y,whpnt);
}

