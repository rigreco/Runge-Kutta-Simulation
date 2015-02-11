ReadMe for C:\AppleX

This is a "customized version" of the Manx Aztec C65 Version 3.2b MS-DOS
cross-development environment for an Apple IIe with 128K of memory running
PRODOS 8.

It is targetted specifically at writing PRODOS SYS programs, and programs that
run under the Aztec C ProDOS Unix-like Shell.

It does not provide support for Apple II's running DOS 3.3. Other than that, 
none of the run-time library functions have been removed that were in the 
original distribution.

Programs are written and compiled on the IBM-PC and then moved to an Apple IIe
or to an emulator disk image to be run.

A modified Graphics link library is provided which has been extended to
support the use of bit-mapped graphics images, sound routines, and the use of
auxiliary memory.

The build environment has been configured to run under Windows XP and a
pre-configured shortcut has been provided for this purpose as well as a make
utility program and some additional programs to be used in conjunction with
make.

Several sample programs are provided, each with its own MAKEFILE and each can
be reviewed for information on how to write your own PRODOS SYS programs.

Getting Started

Unzip the ZIP file with directories intact onto the root of your C: Drive. The
Windows XP shortcut has been pre-configured to use this directory structure.

Open the C:\AppleX folder in MyComputer and click-on the shortcut. A cmd
window will open, and you will be in the C:\AppleX directory which is the
parent directory for this environment. The required environment variables to
build Aztec C PRODOS programs are set for you, and you can build these
anywhere on your computer from this cmd window.

You must be somewhat familiar with DOS commands to use this build environment.

You can test the environment by building the programs in the SAMPLES
subdirectory.

Each has its own MAKEFILE which will build a PRODOS program simply by
typing "make" and pressing [ENTER] while in each's project directory under
SAMPLES.

What You Will Need

You can write your own programs in notepad or your favorite programmer's
editor. This environment doesn't provide an editor.

You should get a copy of the Aztec C Manual which is available online at 

http://www.clipshop.ca/Aztec/cat1.htm and http://www.clipshop.ca/Aztec/cat2.htm

This will provide you with the original text of the printed manual for the C65
compiler and considerably more information than the SAMPLES that are included
in this environment.

You will also need an Apple II emulator like Apple II Oasis that provides a
Disk Manager unless you have a real Apple IIe and can download one at

http://www.clipshop.ca/DiskImages/

You can also download a PRODOS DiskImage at the above URL and delete all but
PRODOS and use it as a master for your own programs.

If you wish to create full-screen bitmapped graphics for the Apple II you may
wish to download the ClipShop program from the following link:

http://www.clipshop.ca

Other than that, all you need is the ability to write and compile programs in
the C programming language.

Review the various ReadMe files in this environment for additional notes.

End of Document
