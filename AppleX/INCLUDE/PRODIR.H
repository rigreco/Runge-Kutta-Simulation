/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : prodir.h
Description  : G2 Library Demo Program
               ProDOS Directory Structures

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use this routine for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


/* the Aztec C runtime library function getfinfo() fetches information from ProDOS
about a file, including volume directories and subdirectories, by issuing the
GET_FILE_INFO ProDOS MLI call, and returns the information about the file
in the following structure... */


struct fileinfo {
	unsigned char access;
	unsigned char file_type;
	unsigned aux_type;
	unsigned char storage_type;
	unsigned blocks_used;
	unsigned mod_date;
	unsigned mod_time;
	unsigned create_date;
	unsigned create_time;
	};


/* based on volume directory header */
struct keyblockheader{
    unsigned char length;   /* low nibble = file name length */
    char name[15];
    unsigned char  reserved[8];
    unsigned create_date;
    unsigned create_time;
    unsigned char  version;
    unsigned char  minversion;
    unsigned char  access;
    unsigned char  entrylength;
    unsigned char  entries;
    unsigned count;
    unsigned pointer;
    unsigned blocks;
    };

/* based on directory file entries */
struct filefind{
    unsigned char length;   /* low nibble = file name length */
    char name[15];
    unsigned char  type;
    unsigned key;
    unsigned blocks;
    unsigned size;
    unsigned char  size3;       /* highest byte of 3 byte filesize integer */
    unsigned create_date;
    unsigned create_time;
    unsigned char  version;
    unsigned char  minversion;
    unsigned char  access;
    unsigned address;   /* load adress (subtype) low-byte */
    unsigned mod_date;
    unsigned mod_time;
    unsigned hdr;
    };





/*

Figure B-3. The Volume Directory Header


    Field                                Byte of
   Length                                Block
          +----------------------------+
  1 byte  | storage_type | name_length | $04
          |----------------------------|
          |                            | $05
          /                            /
 15 bytes /        file_name           /
          |                            | $13
          |----------------------------|
          |                            | $14
          /                            /
  8 bytes /          reserved          /
          |                            | $1B
          |----------------------------|
          |                            | $1C
          |          creation          | $1D
  4 bytes |        date & time         | $1D
          |                            | $1F
          |----------------------------|
  1 byte  |          version           | $20
          |----------------------------|
  1 byte  |        min_version         | $21
          |----------------------------|
  1 byte  |           access           | $22
          |----------------------------|
  1 byte  |        entry_length        | $23
          |----------------------------|
  1 byte  |     entries_per_block      | $24
          |----------------------------|
          |                            | $25
  2 bytes |         file_count         | $26
          |----------------------------|
          |                            | $27
  2 bytes |      bit_map_pointer       | $28
          |----------------------------|
          |                            | $29
  2 bytes |        total_blocks        | $2A
          +----------------------------+

Figure B-4. The Subdirectory Header


    Field                                Byte of
   Length                                Block
          +----------------------------+
  1 byte  | storage_type | name_length | $04
          |----------------------------|
          |                            | $05
          /                            /
 15 bytes /         file_name          /
          |                            | $13
          |----------------------------|
          |                            | $14
          /                            /
  8 bytes /          reserved          /
          |                            | $1B
          |----------------------------|
          |                            | $1C
          |          creation          | $1D
  4 bytes |        date & time         | $1D
          |                            | $1F
          |----------------------------|
  1 byte  |          version           | $20
          |----------------------------|
  1 byte  |        min_version         | $21
          |----------------------------|
  1 byte  |           access           | $22
          |----------------------------|
  1 byte  |        entry_length        | $23
          |----------------------------|
  1 byte  |     entries_per_block      | $24
          |----------------------------|
          |                            | $25
  2 bytes |         file_count         | $26
          |----------------------------|
          |                            | $27
  2 bytes |       parent_pointer       | $28
          |----------------------------|
  1 byte  |    parent_entry_number     | $29
          |----------------------------|
  1 byte  |    parent_entry_length     | $2A
          +----------------------------+

*/


/*  ProDOS 8 Technical Reference Manual
    http://www.easy68k.com/paulrsm/6502/PDOS8TRM.HTM

Figure B-5. The File Entry

  Field                                Entry
 Length                                Offset
          +----------------------------+
  1 byte  | storage_type | name_length | $00
          |----------------------------|
          |                            | $01
          /                            /
 15 bytes /         file_name          /
          |                            | $0F
          |----------------------------|
  1 byte  |         file_type          | $10
          |----------------------------|
          |                            | $11
  2 bytes |        key_pointer         | $12
          |----------------------------|
          |                            | $13
  2 bytes |        blocks_used         | $14
          |----------------------------|
          |                            | $15
  3 bytes |            EOF             |
          |                            | $17
          |----------------------------|
          |                            | $18
          |          creation          |
  4 bytes |        date & time         |
          |                            | $1B
          |----------------------------|
  1 byte  |          version           | $1C
          |----------------------------|
  1 byte  |        min_version         | $1D
          |----------------------------|
  1 byte  |           access           | $1E
          |----------------------------|
          |                            | $1F
  2 bytes |          aux_type          | $20
          |----------------------------|
          |                            | $21
          |                            |
  4 bytes |          last mod          |
          |                            | $24
          |----------------------------|
          |                            | $25
  2 bytes |       header_pointer       | $26
          +----------------------------+

*/

