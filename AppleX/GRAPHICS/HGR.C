hgr()
{
	char *gswitch=(char*)0xc050;
    char *hswitch=(char*)0xc055;
	char *tswitch=(char*)0xc052;
	char *mswitch=(char*)0xc057;

	gswitch[0]=0x00; /* graphics */
    hswitch[0]=0x00; /* secondary page */
	tswitch[0]=0x00; /* full screen */
	mswitch[0]=0x00; /* hi_res */
}
