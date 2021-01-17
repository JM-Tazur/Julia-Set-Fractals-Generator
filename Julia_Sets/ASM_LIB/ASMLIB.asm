.data
	zReal REAL8 0.0
	zImg REAL8 0.0
	cReal REAL8 0.0
	cImg REAL8 0.0
	rReal Real8 0.0
	rImag Real8 0.0
	two REAL8 2.0
	dist REAL8 0.0
	three REAL8 3.0
	fpuStatus word 0
	result dword 0

.code

INSETproc1 proc 
	mov rbx, qword ptr [rcx]		;z.real -> zReal
	mov zReal, rbx

	mov rbx, qword ptr [rcx+8]		;z.real -> zImg
	mov zImg, rbx

	mov rbx, qword ptr [rdx]		;z.real -> zReal
	mov cReal, rbx

	mov rbx, qword ptr [rdx+8]		;z.real -> zReal
	mov cImg, rbx

	mov ecx, 0

	BeginingOfCalculatonLoop:
		;---------------------------------------------------
		;z = z*z = (z.real+i*z.img)*(z.real+i*z.img)=z.real*zreal + i*2*z.real*z.img -z.img*z.img = (z.real*z.real - z.img*z.img) + i(2*z.real*z.img)

		movsd xmm0, zReal			;xmmo <- z.real
		mulsd xmm0, zReal			;xmm0 = z.real*z.real
		movsd xmm6, zImg			;xmm6 <- z.img
		mulsd xmm6, zImg			;xmm6 = zImg*zImg
		subsd xmm0, xmm6			;xmm0 = (z.real*z.real - z.img*z.img)

		movsd xmm1, two				;xmm1 <- 2.0
		mulsd xmm1, zReal			;xmm1 = 2*z.real
		mulsd xmm1, zImg			;xmm1 = (2*z.real*z.img)

		;------------------------------------------------------
		;z = z + c = (z.real+ c.real) + i(z.img+c.img)
		addsd xmm0, cReal			;xmm0 = z.real + c.real
		addsd xmm1, cImg			;xmm1 = z.img + c.img
		movsd zReal, xmm0
		movsd zImg, xmm1

		;---------------------------------------------------------
		;dist = (z.real*z.real) + (z.img*z.img)
		movsd xmm6, xmm0			;xmm6 <- z.real
		mulsd xmm6, xmm0			;xmm0 = z.real*z.real
		movsd xmm7, xmm1			;xmm6 <- z.img
		mulsd xmm7, xmm1			;xmm1 = z.img*z.img
		addsd xmm6, xmm7			;xmm6 = (z.real+z.real) + (z.img+z.img)

		movsd dist, xmm6 
		
		;------------------------------------
		fld three					;st0 <- liczba1 push
		fld dist					;st1 <- liczba2 push
		
		fcompp
		fstsw fpuStatus				;fpuStatus <- FPU status flags
		mov ax, fpuStatus
		
		and eax, 0100011100000000B	;operacja and
		cmp eax, 0000000000000000B	;porownanie do 0
		je	breakingLoop			;jump if st0 > st1		
		 		
		inc ecx
		cmp ecx, 512
	jne BeginingOfCalculatonLoop	;end of calculation loop

		mov result, 0
		jmp afterBreakingLoop

	breakingLoop:
		mov result, ecx

	afterBreakingLoop:
		mov rax, 0
		mov eax, result
		ret

INSETproc1 endp
end