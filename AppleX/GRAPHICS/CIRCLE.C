int __x_aspect=1, __y_aspect=1;

circle(cx,cy,r)
int cx,cy,r;
{

    int x,y,a,b,c,d,f,m,n;
    /* replaced double z=1.16 with long integer 116
       so fake floating point and divide product by 100

       February 2013 */
	long z=116L;

    x=r; y=0; b=1; f=0;

    a=(-2)*x+1;
	m=__x_aspect;
	n=__y_aspect;

point:


   /* replaced double z=1.16 with long integer 116
      so fake floating point and divide product by 100

      February 2013 */

	c=   (int)((z*x)/100);
	d=   (int)((z*y)/100);


    plot(c*m+cx,y*n+cy);
	plot(d*m+cx,x*n+cy);
    plot(-d*m+cx,x*n+cy);
    plot(-c*m+cx,y*n+cy);
    plot(-c*m+cx,-y*n+cy);
	plot(-d*m+cx,-x*n+cy);
    plot(d*m+cx,-x*n+cy);
    plot(c*m+cx,-y*n+cy);

    if(b>= -a)
        goto fin;

    y+=1; f+=b;
    b+=2;

    if(f>r)
    {
        f+=a;
        a+=2;
        x-=1;
    }
    goto point;

fin:
  ;
}
