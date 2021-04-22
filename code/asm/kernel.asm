; kernel for LINK_01
; build with 'dasm kernel.asm -f3'

	processor 6502

	seg
	org $e000

KernelStart:
	jsr ClearZeroPage
	ldx #$ff
	txs
	lda #$00
	ldy #$00
Start:
	ldx #$00
Increment:
	inc $1000
	jsr Subroutine
	cpx #$80
	bne Increment
	jmp Start

Subroutine:
	inx
	rts

ClearZeroPage:
	lda #$00
	sta $00
	tay
ClearZeroPageLoop:
	dey
	sta $00,y
	bne ClearZeroPageLoop
	rts

	org $fffc
	.word KernelStart
	.word KernelStart
	end
