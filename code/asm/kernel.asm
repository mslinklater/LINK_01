; kernel for LINK_01

	processor 6502

	seg
	org $e000

KernelStart:	
	ldx #$00
Increment:
	inx
	bne Increment
	jmp KernelStart

	org $fffc
	.word KernelStart
	.word KernelStart
	end
