/*	Copyright (C) 1985 by Manx Software Systems, Inc. */
/*  Copyright (C) 1988 by Michael W. Spille */

#include	<prodos.h>
#include	<sysfunc.h>

extern struct shvar {
	char			vects[6];
	int				retflg;
} *_Sp;

_exit(n)
{
	char *temp;
	temp = 0x3f4;

	_sys_parm[0] = 1;
	_sys_parm[1] = 0;				/* close all files */
	_system(SYS_CLOSE);
	if (_Sp)						/* if called from SHELL */
		_Sp->retflg = n;

	*temp++;
	
	_sys_parm[0] = 4;
	_sys_parm[1] = 0;
	_sys_parm[2] = 0;
	_sys_parm[3] = 0;
	_sys_parm[4] = 0;
	_sys_parm[5] = 0;
	_sys_parm[6] = 0;
	_system (0x65);

}

