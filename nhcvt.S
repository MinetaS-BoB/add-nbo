.intel_syntax noprefix

.section .text

__chk_endian:
	sub		rsp, 8
	xor 	eax, eax
	mov		word ptr [rsp], 0x1
	mov		al, byte ptr [rsp]
	add		rsp, 8
	mov		qword ptr _ptr_chk_endian[rip], 0
	mov		byte ptr _Sv_endian_[rip], al
	ret

	.global _ntohl
	.type   _ntohl, @function

_ntohl:
	cmp		qword ptr _ptr_chk_endian[rip], 0
	jz		$+7
	call	__chk_endian
	cmp		byte ptr _Sv_endian_[rip], 0
	jz		$+4
	bswap	edi
	mov		eax, edi
	ret


.section .data

_ptr_chk_endian:
	.quad __chk_endian


.section .bss

_Sv_endian_:
	.byte