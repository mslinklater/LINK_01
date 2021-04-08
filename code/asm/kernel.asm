; kernel for LINK_01

	processor 6502

	seg
	org $e000

KernelStart:	nop

	org $fffc
	.word KernelStart
	.word KernelStart
	end
