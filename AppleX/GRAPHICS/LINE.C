int plot(), bplot(), gplot(), rplot(), vplot();

drw(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
	comline(x1,y1,x2,y2,plot);
}

bdrw(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
	comline(x1,y1,x2,y2,bplot);
}

gdrw(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
	comline(x1,y1,x2,y2,gplot);
}

rdrw(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
	comline(x1,y1,x2,y2,rplot);
}

vdrw(x1,y1,x2,y2)
int x1,y1,x2,y2;
{
    comline(x1,y1,x2,y2,vplot);
}


int __oldx=0, __oldy=0;

lineto(x,y)
int x,y;
{
	drw(__oldx,__oldy,x,y);
}

blineto(x,y)
int x,y;
{
	bdrw(__oldx,__oldy,x,y);
}

glineto(x,y)
int x,y;
{
   	gdrw(__oldx,__oldy,x,y);
}

vlineto(x,y)
int x,y;
{
	vdrw(__oldx,__oldy,x,y);
}

rlineto(x,y)
int x,y;
{
    rdrw(__oldx,__oldy,x,y);
}


static int
comline(x1,y1,x2,y2,func)
int (*func)();
{
	register int dx,dy,ix,iy;
	int e,ei,ed,i;

	__oldx=x2; __oldy=y2;
	dx=x2-x1;
	dy=y2-y1;
	ix=1;
	if(dx<0)
		{ ix=-1;
		  dx=-dx;
		}
	iy=1;
	if(dy<0)
		{ iy=-1;
		  dy=-dy;
		}
	if(dy>dx)
		goto ylin;

	ei=2*dy;
	ed=ei-2*dx;
	e=-dx+ei;
	for(i=1;i<=dx;++i){
		(*func)(x1,y1);
		x1=x1+ix;
		if(e<0)
			e=e+ei;
		else{ 
			y1=y1+iy;e=e+ed;
		}
	}
	goto fin;

ylin:

	ei=2*dx;
	ed=ei-2*dy;
	e=-dy+ei;
	for(i=1;i<=dy;++i)
		{ (*func)(x1,y1);
		  y1=y1+iy;
		  if(e<0)
			e=e+ei;
		  else{ x1=x1+ix;e=e+ed;}
		}
fin:		  
;		   
}

