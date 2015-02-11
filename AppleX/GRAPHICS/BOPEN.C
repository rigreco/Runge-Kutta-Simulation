/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : bopen.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Revision Date: May 31, 1991

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* bopen.c binary open */

#include	<fcntl.h>
#include	<prodos.h>
#include	<errno.h>
#include	<sysfunc.h>
#include	<sgtty.h>
#include	<device.h>

bopen(uname, flags, mode)
char *uname;
{
	register int dev, err, fd;
	register struct _fil_buf *fb;
	register char *iobuf;
	register struct _name_dev *dp;
	int mflg = 0;
	char name[64];
	struct finfo f;
	char *_get_iob();

	for (fb=_fil_tab;fb<_fil_tab+MAXFILES;fb++)
		if (fb->unit == 0)
			goto found;
	errno = EMFILE;
	return(-1);
found:
	fb->flags = flags & 0x03;
	fd = fb - _fil_tab;

	for (dp=&_dev_info->dev_con;dp<=&_dev_info->dev_ser;dp++) {
		if (strequ(uname, dp->dev_nam) == 0) {
			dev = dp->dev_num;
			goto gotdev;
		}
	}
	if (uname[3] == 0 && uname[2] == ':' && toupper(uname[0]) == 'S') {
		dev = uname[1] - '0';
gotdev:
		if ((dev&0x40) == 0)
			_slot_open(&_dev_info->slots[dev&7]);
		fb->unit = dev | 0x80;
		return(fd);
	}

	if ((iobuf = _get_iob(fd)) == 0)
		return -1;

	if (_fixnam(uname, name))
		return(-1);
	ctop(name);
again:
	*_sys_parm = 3;
	*(char **)(_sys_parm + 1) = name;
	*(char **)(_sys_parm + 3) = iobuf;
	if (err = _system(SYS_OPEN)) {
		if (err != 0x44 && err != 0x46) {
	xerr:
			errno = err;
			return(-1);
		}
		if ((flags&O_CREAT) == 0) {
			err = ENOENT;
			goto xerr;
		}

		*_sys_parm = 7;
		*(char **)(_sys_parm + 1) = name;
		*(_sys_parm + 3) = 0xc3;	/* enable everything */
        *(_sys_parm + 4) = 6;       /* binary type file */
		*(int *)(_sys_parm + 5) = 0;
		*(_sys_parm + 7) = 1;		/* file, not directory */
		*(long *)(_sys_parm + 8) = 0;
		if (err = _system(SYS_CREAT))
			goto xerr;
		flags &= ~(O_EXCL|O_CREAT|O_TRUNC);
		mflg = 1;
		goto again;
	}

	fb->unit = _sys_parm[5];
	if ((flags&(O_CREAT|O_EXCL)) == (O_CREAT|O_EXCL)) {
		close(fd);
		err = EEXIST;
		goto xerr;
	}
	if (flags & O_TRUNC)
		_seteof(fd, 0L);
	else if (flags & O_APPEND)
		lseek(fd, 0L, 2);
	if (mflg) {
		_getfinfo(uname, &f);
		f.access = mode;
		_setfinfo(uname, &f);
	}
	return(fd);
}

