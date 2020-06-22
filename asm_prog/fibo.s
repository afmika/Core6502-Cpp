lda #$01
sta $24
lda #$02
sta $25

ldx #$10 ; 10-th term
stx $26
start:
	txa
	lda $24 ; load the first op
	adc $25 ; add the first op to the second
	sta $24 ; store the result in $0024 to replace the old first op
	ldx $25
	inx ; new second op
	stx $25
	cpx $26
	bne start
brk


