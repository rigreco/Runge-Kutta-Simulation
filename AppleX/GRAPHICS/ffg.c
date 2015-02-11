/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : ffg.c
Description  : G2 Library Routines for Reading file lists etc.
               from ProDOS Directories.

               Call in the following order:

               gfindopen()
               gfindnext()
               ggfindclose()

               Read the code and comments and see the demo piclist.c
               for more info.

               See prodir.h and demo program ld.c for more comments
               and even more info.

               Note: recursion is not supported and these
               routines are designed for only a single instance.

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

#include <stdio.h>
#include <prodir.h>

/* internal - for information call 411 */
int gfindcount(cnt)
int cnt;
{
	static int fcount = 0;

	if (cnt != 411) fcount = cnt;

	return fcount;
}

/* internal - for information call 411 */
int gfindhandle(fh)
int fh;
{
	static int fhandle = -1;

	if (fh != 411) fhandle = fh;

	return fhandle;
}


/* closes a ProDOS directory after calling findnext */
int gfindclose()
{
	int fh = gfindhandle(411);
	if (fh != -1) {
		close(fh);
		gfindhandle(-1);
	}
	gfindcount(0);
}


/* opens a ProDOS directory prior to calling findnext

   arg - path - if null uses current directory

   closes prior open directory if any.

   if successful

   - sets gfindhandle for findfirst
   - sets gfindcount for findfirst
   - returns a valid file handle

   otherwise closes directory if open and returns error

 */

int gfindopen(path,pathinfo)
char *path;
struct fileinfo *pathinfo;
{
	char pathname[64], buf[43];

    int fh = -1;

    gfindclose();

    if (NULL == path) {
		if (getprefix (pathname) == -1)return -1;
	}
	else strcpy(pathname,path);

	if (getfinfo (pathname, pathinfo) == -1) return -2;
	if (pathinfo->file_type != 15) return -3;

    if ((fh = open (pathname, 0, 0)) < 0)return -4;

	if (read (fh, buf, 43) < 43) {
		close (fh);
		return -5;
	}

    gfindhandle(fh);
	gfindcount(1);

return fh;

}


/* args - input - filetype - a valid ProDOS filetype - if 0 any filetype will be returned.
          input - ext - extension without the dot - if null any extension will be returned.

          input, output - filename - char[16] - must not be null
                        - filefind structure - must not be null

          returns 0 if successful
          returns -1 if done (directory is closed when done)
          returns -2 if directory has not been opened prior to calling
*/

int gfindnext(filetype, ext, filename, ff)
int filetype;
char *ext, *filename;
struct filefind *ff;
{


	char buf[16];
	int fh, count, i, j, filelength;

    fh = gfindhandle(411);
    if (fh < 0) return -2;

    count = gfindcount(411);
    filename[0] = 0;

    if (NULL != ext) {
	   for (i = 0; ext[i] != 0; i++) ext[i] = toupper(ext[i]);
	}


    for (;;) {

        if (read (fh,ff,39) < 39) break;
        if (ff->type == 0) break;

        count++;
        gfindcount(count);

        if (count == 13)
        {
	        read (fh,buf,5);
            count = 0;
            gfindcount(count);;
        }


        filelength = (ff->length & 0xf);

        if (filelength != 0)
        {

            if (filetype == 0 || (filetype == (int)ff->type)) {

				if (NULL == ext) {
                	strncpy(filename, ff->name, filelength);
                	filename[filelength] = 0;
					return 0;
				}
				j = -1;
				for (i = 0; i < filelength; i++) {
				   if (j > -1) {
					   buf[j] = toupper(ff->name[i]);
					   j++;
					   buf[j] = 0;
				   }
				   if (ff->name[i] == '.') j = 0;
				}
				if (j != -1) {
				    for (i = 0; ext[i] != 0; i++) {
						if (ext[i] == '?') continue;
						if (ext[i] != buf[i]) {
							j = -1;
							break;
						};
					}

				}
				if (j!= -1) {
                	strncpy(filename, ff->name, filelength);
                	filename[filelength] = 0;
					return 0;

				}
 			}
        }
	}

    close (fh);
    gfindhandle(-1);
    gfindcount(0);
    ff->name[0] = 0;
    ff->length = 0;
    ff->type = 0;


	return -1;
}
