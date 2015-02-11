/* adjust HGR scanline array from page 2 to page 1
   to use existing loaders for ProDOS SYS programs in
   programs that use graphics page 1 (i.e. shell programs) */
extern unsigned HB[];

hbsh()
{
	unsigned y;

	if (HB[0] == 0x4000) {
		for (y= 0; y < 192;y++) HB[y] = (HB[y] - 0x2000);
	}
}
