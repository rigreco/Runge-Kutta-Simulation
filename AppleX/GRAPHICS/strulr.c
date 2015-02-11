/* ------------------------------------------------------------------------
System       : Manx Aztec C65 Version 3.2b
               MS-DOS cross-development environment
Platform     : Apple IIe 128K PRODOS 8
Program      : strulr.c
Description  : G2 Library Routine

Written by   : Bill Buckels
Date Written : January 2013
Revision     : 1.0 First Release
Licence      : You may use these routines for whatever you wish as long
               as you agree that Bill Buckels has no warranty or
               liability obligations whatsoever from said use.
------------------------------------------------------------------------ */


strlwr(str)
char *str;
{
	int i;
	char AZ;

	for (i = 0; str[i] != 0; i++) {
		AZ = str[i];
		if (AZ > 64 && AZ < 91) str[i] = (AZ + 32);
	}

}

strupr(str)
char *str;
{
	int i;
	char az;

	for (i = 0; str[i] != 0; i++) {
		az = str[i];
		if (az > 96 && az < 123) str[i] = (az - 32);
	}
}