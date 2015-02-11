page1()
{
	*(char *)0xc054=0x00; /* primary page */
}

page2()
{
	*(char *)0xc055=0x00; /* secondary page */
}

