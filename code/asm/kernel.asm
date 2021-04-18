; kernel for LINK_01
; build with 'dasm kernel.asm -f3'

	processor 6502

	seg
	org $e000

KernelStart:
	ldx #$ff
	txs
	lda #$00
	ldy #$00
Start:
	ldx #$00
Increment:
	inc $1000
	inx
	bne Increment
	jmp Start

	org $fffc
	.word KernelStart
	.word KernelStart
	end
