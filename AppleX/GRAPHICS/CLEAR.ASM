;/* ------------------------------------------------------------------------
;System       : Manx Aztec C65 Version 3.2b
;               MS-DOS cross-development environment
;Platform     : Apple IIe 128K PRODOS 8
;Program      : clear.asm
;Description  : G2 Library Routine
;
;               HGR routine from original Aztec C distribution 
;               Modified by me to use Page 2 for compatibility with
;               ProDOS SYS programs.
;
;Original      : Dec 30, 1990
;Probably by   : Jim Goodnow 
;
;Modified by   : Bill Buckels
;Revision Date : January 2013
;
;Licence      : You may use this code for whatever you wish as long
;               as you agree that Bill Buckels has no warranty or
;               liability obligations whatsoever from said use.
;------------------------------------------------------------------------ */

R0 equ 8
SP equ 2

clr lda #0 ;store ptr in R0
 sta R0
 lda #$40
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
 cmp #$60
 bcc loop
 lda $c057 ;high res
 lda $c055 ;page 2
 lda $c052 ;full graphics
 lda $c050 ;graphics
 rts
 
	public	black_
black_	
	lda	#0
	sta	R0+2
	sta	R0+3
	jmp	clr
	public	blue_
blue_	
	lda	#$d5
	sta	R0+2
	lda	#$aa
	sta	R0+3
	jmp	clr
	public	violet_
violet_	
	lda	#$55
	sta	R0+2
	lda	#$2a
	sta	R0+3
	jmp	clr
	public	green_
green_	
	lda	#$2a
	sta	R0+2
	lda	#$55
	sta	R0+3
	jmp	clr
	public	red_
red_	
	lda	#$aa
	sta	R0+2
	lda	#$d5
	sta	R0+3
	jmp	clr
	public	white_
white_	
	lda	#$7f
	sta	R0+2
	lda	#$7f
	sta	R0+3
	jmp	clr	
