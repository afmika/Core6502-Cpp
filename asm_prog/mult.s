ldx #$02
ldy #$04
stx $0024
mult:
	adc $0024
	sta $0025
	dey
	bne mult ; branch on non equal
BRK