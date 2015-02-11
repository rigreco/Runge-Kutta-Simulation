
		public ldnjmp_
		public elnj_
		public open_parms_
		public read_parms_
		cseg
ldnjmp_
		lda	#0			
		ldx	#$17			;number of bytes to clear in system bitmap
looper		sta	$bf58,x		;clear out this byte in the bitmap
		dex
		bne	looper			;go until all done

		lda	$f3
		sta	$bf58			;Protect stack & sytstem bitmap
		lda	#1
		sta	$bf6f

		lda	#$80			;Low byte of 0x280 (addr of file to be sexec'd)
		sta	open_parms_+1
		lda	#$02			;High byte of 0x280
		sta	open_parms_+2
		jsr	$bf00			;Do open MLI call
		fcb	$c8
		fdb	open_parms_
		bne 	end

		lda #$4				;Parameter count for read call is 4
		sta	read_parms_
		lda	fd				;Get file descriptor from open & put it in read
		sta	fd2
		jsr	$bf00			;Read in the file
		fcb	$ca
		fdb	read_parms_
		bne	end

		lda	#1				;Parameter count for close call is 1
		sta	read_parms_
		jsr	$bf00			;Close the file
		fcb	$cc
		fdb	read_parms_

		dec	$3f4			;Invalidate power-up byte
		jmp	$2000			;Jump to now-resident program

end		sta	08				;oops! and error occured!  Put error in ret. reg
		lda	#0
		sta	09				;err code is a char so zero-out high byte
		rts

; MLI parameter tables follow...

open_parms_	
		fcb	3
		fcb	0
		fcb	0
		fcb	0
		fcb	$17
fd		fcb	0

read_parms_	
		fcb	4
fd2		fcb	$27
		fcb	$00
		fcb	$20
blocks2		fcb	$00
		fcb	$90
		fcb	0
		fcb	0
stuffy
		fcb	1
		fcb	0
elnj_						;Marks end of ldnjmp routine
