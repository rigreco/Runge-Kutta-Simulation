;/* ------------------------------------------------------------------------
;System       : Manx Aztec C65 Version 3.2b
;               MS-DOS cross-development environment
;Platform     : Apple IIe 128K PRODOS 8
;Program      : clear1.asm
;Description  : G2 Library Routine
;
;               HGR routine from original Aztec C distribution 
;               Slightly Modified by me 
;               Compatibility with Aztec C Programs that use
;               Page 1 HGR (shell programs, DOS 3.3 programs)
;
;Original      : Dec 30, 1990
;Probably by   : Jim Goodnow 
;
;Modified by   : Bill Buckels
;Revision Date : February 2013
;
;Licence      : You may use this code for whatever you wish as long
;               as you agree that Bill Buckels has no warranty or
;               liability obligations whatsoever from said use.
;------------------------------------------------------------------------ */

R0 equ 8
SP equ 2

sclr lda #0 ;store ptr in R0
 sta R0
 lda #$20
 sta R0+1
 ldy #0
loop
 lda R0+2
 sta (R0),Y
 iny
 lda R0+3
 sta (R0),Y
 iny
 bne loop
 ldx R0+1
 inx
 stx R0+1
 txa
 cmp #$40
 bcc loop
 lda $c057 ;high res
 lda $c054 ;page 1
 lda $c052 ;full graphics
 lda $c050 ;graphics
 rts
  
	public	sblack_
sblack_	
	lda	#0
	sta	R0+2
	sta	R0+3
	jmp	sclr
	public	sblue_
sblue_	
	lda	#$d5
	sta	R0+2
	lda	#$aa
	sta	R0+3
	jmp	sclr
	public	sviolet_
sviolet_	
	lda	#$55
	sta	R0+2
	lda	#$2a
	sta	R0+3
	jmp	sclr
	public	sgreen_
sgreen_	
	lda	#$2a
	sta	R0+2
	lda	#$55
	sta	R0+3
	jmp	sclr
	public	sred_
sred_	
	lda	#$aa
	sta	R0+2
	lda	#$d5
	sta	R0+3
	jmp	sclr
	public	swhite_
swhite_	
	lda	#$7f
	sta	R0+2
	lda	#$7f
	sta	R0+3
	jmp	sclr	
