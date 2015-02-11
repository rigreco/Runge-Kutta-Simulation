/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : d2save.c
Description  : G2 Library Routine
               DHGR Save for ProDOS SYS Programs
               Saves 3 formats from DHGR Page 2:

               0 - BIN/AUX BSaved Pairs
               1 - A2FC BSaved Chunks
               2 - DHR Raw Raster Images

               Overwrites existing file if it exists.
               Danger Will Robinson! If a write error
               occurs the damaged file(s) will be
               removed and all will be lost.

               Does Not Save Run-Length Encoded DHX
               XPacked Images nor XCrunched XCC and
               XRC color indices which take altogether
               too long to uncrunch to make them
               practical for most things at time of
               this writing.

Written by   : Bill Buckels
Revision Date: February 2013

Licence      : You may use this code for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */

/* save a file from double hires screen 2
   in 2 formats - A2FC or DHR */
#include <fcntl.h>
#include <prodir.h>

extern unsigned HB[];

#define BLOCK_SIZE 3840

int d2save(basename,ftype)
char *basename;
int ftype;
{
	unsigned int src,src2,target;
    int fh,i=0,j=0,status=-2,y,x,x1,x2;
    char hdr[5], binfile[20], auxfile[20], *workbuf = (char *)4192, *ptr;
    struct fileinfo *fi = (struct fileinfo *)4192;

    /* allow filetype to be specified by ascii numeric value to
       simplify calls using keyboard input logic */
    if (ftype > 47 && ftype < 58) ftype -= 48;


    /* create output names for save from basename */
	for (;;) {
	  auxfile[i] = binfile[i] = basename[i];
	  if (binfile[i] == 0 || binfile[i] == '.') {
		  auxfile[i] = '.'; binfile[i++] = '.';
		  break;
	  }
	  i++;
	}

    /* remove any existing extension and add our standard
       3 character extension for the filetype specified */
    if (ftype == 0) {
	   auxfile[i] = 'A'; binfile[i++] = 'B';
	   auxfile[i] = 'U'; binfile[i++] = 'I';
	   auxfile[i] = 'X'; binfile[i++] = 'N';
	}
	else if (ftype == 1) {
	   auxfile[i++] = '2';
	   auxfile[i++] = 'F';
	   auxfile[i++] = 'C';
	}
	else {
	   /* also create DHR header */
	   hdr[j++] = auxfile[i++] = 'D';
	   hdr[j++] = auxfile[i++] = 'H';
	   hdr[j++] = auxfile[i++] = 'R';
	   hdr[j++] = 80;
	   hdr[j]   = 192;
	}
	auxfile[i] = binfile[i] = 0;

    /* when Aztec C creates a file in ProDOS the filetype is set to 4 (text file).
       in the past I modified the code for open to create binary files (filetype 6)
       and called my function bopen which is part of the G3 library.
       however the bopen code duplicates the aztec c code for open with this one
       small change and therefore creates a larger program when open is also used
       in the same program.

       an alternative method to work around this is to create the file, close it,
       modify the filetype from text to binary using setfinfo and then re-open the
       file and write to it. See below. Since I wanted to set the load address
       anyway I kill two birds with one stone by using setfinfo.

       I have no idea why the Aztec C developers did not use a bitmask like
       microsoft did to specify a binary or text file.
    */

	if((fh=open(auxfile, O_WRONLY|O_TRUNC|O_CREAT,0xc3)) == -1) return -1;
	close(fh);

    /* call ProDOS to set the file type to binary and
       the subtype to the load address */
    /* set load address to screen 1 for AUX file
       BASIC programs may expect this */

	if (getfinfo (auxfile, fi) != -1) {
	   fi->file_type = 6;
	   if (ftype == 0) fi->aux_type = 0x2000; /* screen 1 */
	   else fi->aux_type = 0x4000; /* screen 2 */
	   setfinfo(auxfile,fi);
	}
	if((fh=open(auxfile, O_WRONLY,0xc3)) == -1) {
		unlink(auxfile);
		return -1;
	}


    /* save screen based on filetype specified */

    /* write AUX or A2FC file */
    if (ftype == 0 || ftype == 1) {
		/* move 8192 bytes from auxiliary screen memory and write to file */
		src = 0x4000;
		auxtomain(src,src+3999,4192);
		for (;;) {
			if (write(fh,workbuf,4000) != 4000) break;
			src+=4000;
			auxtomain(src,src+3999,4192);
            if (write(fh,workbuf,4000) != 4000) break;
            src+=4000;
			auxtomain(src,src+191,4192);
            if (write(fh,workbuf,192) != 192) break;
            /* add 8192 bytes to A2FC from main screen memory */
            if (ftype == 1) {
				if (write(fh,(char *)0x4000,0x2000) != 0x2000) break;
			}
			status =0;
			break;
		}
	}
	else if (write(fh,hdr,5) == 5) {
		/* write DHR file - if no error from writing the header
		                    write the image data */
	   status = 0;
	   y = 0;
	   /* write 4 blocks of 48 scanlines */
	   for (x = 0; x < 4; x++) {

		   /* move 48 scanlines into write buffer area at 4192
		      interleaving auxmem with mainmem rasters */
		   for (x1 = 0, x2=40; x1 < BLOCK_SIZE; x1+=80,x2+=80) {

                /* move a scanline from auxiliary screen memory
                   every even 40 bytes in the buffer */
                src =  HB[y];
                src2 = src+39;
				target = (unsigned int)&workbuf[x1];
				auxtomain(src,src2,target);

				/* interleaf a scanline from main screen memory
				   for the following 40 bytes */
				ptr = (char *)src;
				target = (unsigned int)&workbuf[x2];
				movmem(ptr,target,40);
				y++;
		   }

		   /* write the block and check for errors */
		   if (write(fh,workbuf,BLOCK_SIZE) < BLOCK_SIZE) {
				status = -2;
				break;
			}
		}
	}

    close(fh);

    /* if a write error has occurred remove
       the partial file and outa' here */
    if (status != 0) {
		unlink(auxfile);
        return status;
	}

    if (ftype != 0) return 0;

    /* if writing BIN/AUX file pairs save main screen memory
       directly to the BIN file - for the other filetypes
       there is no second file */
    status = -3;
	for(;;) {
		if((fh=open(binfile, O_WRONLY|O_TRUNC|O_CREAT,0xc3)) == -1) break;
		close(fh);
		if (getfinfo (binfile, fi) != -1) {
			fi->file_type = 6;
			fi->aux_type = 0x2000;
		   	setfinfo(binfile,fi);
		}
        if((fh=open(binfile, O_WRONLY,0xc3)) == -1) break;
	   	status = 0;
	   	if (write(fh,(char *)0x4000,0x2000) != 0x2000) status = -4;
	   	close(fh);
	    break;
	}

	if (status != 0) {
		unlink(auxfile);
		unlink(binfile);
	}

	return status;

}
