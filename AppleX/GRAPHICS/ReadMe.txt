ReadMe for the C:\AppleX\GRAPHICS subdirectory

This subdirectory contains the source code for a modified and enhanced version
of the graphics library that was originally shipped with the Aztec C 6502
cross-compiler. It is called G2.LIB

It also contains a makefile which can be used to build a new version of this
library should you decide to add your own routines or modify the routines that
have been provided. You will have no need to build a new version of the
library other than that since the G2.LIB that this makefile produces is
already in place in the C:\AppleX\LIB subdirectory.

This library is targetted at PRODOS 8 running on an Apple IIe with 128K of
memory

This library was developed by Canadian Software Developer Bill Buckels for
an educational software project in the early 1990's called the "Collection Les
Petites espadrilles" for use in Elementary Schools. The programs were based on
their IBM-PC counterparts which had been released a couple of years prior to
the Apple versions and the expectation was that the Apple versions would
behave as closely as possible to the IBM versions.

The Manx C compiler provided a rudimentary Graphics Library, but came nowhere
close to what Bill needed to complete the four programs in the "Collection Les
Petites espadrilles" that he had undertaken to write. So he set to work to
create the graphics and the sound routines that the Apple versions needed to
behave as closely as possible to their IBM-PC counterparts.

The graphics used in the IBM-PC versions (4 Color CGA Mode) were vastly
different from Apple II graphics (which were a coarser resolution), and each
and every screen and graphics image needed to be redrawn, and reformatted for
the Apple II. Using the Graphics from the IBM-PC version as a starting point,
Bill developed his own Apple II graphics file formats and programmed his own
set of conversion tools which he ran on the IBM-PC to produce the Apple II
graphics after creating and editing these in IBM-PC format to suit the Apple
II display. He did this in conjunction with writing his Manx C graphics
library, since both tasks were complimentary. When the graphics images and
graphics and sound library routines were completed he moved forward to writing
the programs.

Not only did the Apple II have less capable graphics than the IBM-PC; it also
ran more slowly with only 128K of memory, some of it unusable, and with slower
disk access and a smaller floppy disk size. To overcome all of this Bill broke
his Manx C Apple programs into small modules called "overlays" which ran in
very little memory, and he used the upper ram bank of the Apple II to store
his graphics libraries and other data to avoid loading from disk where
possible. Since the Manx C compiler translates its programs into machine
language which runs as quickly as can be on the Apple II, no optimization or
additional "tweaks" were required, except to script the game levels using
external scripts (also of Bill's design) which further saved on disk space and
program memory, and which avoided slow processor intensive operations that
would otherwise have been needed.

The finished results ran more slowly than their IBM-PC counterparts, but for
all practical purposes had all the same functionality.

The G2.LIB contains all the library routines used in the Apple versions of the
"Collection Les Petites espadrilles" and greatly extends the Aztec C 6502
programming environment. These routines are not exclusively limited to
graphics and include sound and keyboard routines as well.

Review the source code and sample programs for more information.

End of ReadMe
