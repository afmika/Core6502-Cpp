; This program will count from $00 to $64 ([Note] $64 = 100 )
; we can use it to list even numbers
LDA #$00 ; starting with zero
ADC #$02
TAX
CPX #100 ; upper bound (100 in base 10)
BNE $02  ; on nonequal : goto offset $0002 (ADC in our case) 