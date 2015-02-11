/* :ts=4 */
/* SEXEC - Exec for system programs */
/* Copyright (c) 1988 by Michael W. Spille */

#include <prodos.h>
#include <sysfunc.h> 

char *ctop();
extern void ldnjmp ();
extern void elnj ();

sexec (pname)
char *pname;
{
	char *system_path, *rest_code;
	int (*sys_prog)();
	char *lptr, *eptr;
	int ret_code;

	rest_code = (char *)0x1000;
	system_path = 0x280;
	lptr = (char *)&ldnjmp;
	eptr = (char *)&elnj;

/*  Convert pname from ASCIIZ to pascal length-string convention and copy it to
	0x280, where prodos expects it to be. */

	strcpy (system_path,pname);
	ctop(system_path);

	_sys_parm[0] = 1;		/* Parm count is 1 */
	_sys_parm[1] = 0;
	_system(SYS_CLOSE);		/* Close all files */

/* Move ldnjmp down to 0x1000 */

	for (;lptr != eptr;)
		*rest_code++ = *lptr++;

/* Jump to the loader */

	sys_prog = 0x1000;
	ret_code = (*sys_prog)();	/*  There should be no return from this call */
							 /*  If there is a return, ldnjmp couldn't load the 
								system program @ 0x2000, and will return the
								prodos error message (in decimal) */
	return (ret_code);
}

