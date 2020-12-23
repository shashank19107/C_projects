;Shashank Dargar
;2019107

bits 16
org 0x7c00

boot:
	mov ax, 0x2401
	int 0x15
	mov ax, 0x3
	int 0x10
	cli
	lgdt [gdt_pointer]
	mov eax, cr0
	or eax,0x1
	mov cr0, eax
	jmp CODE_SEG:boot32
gdt_start:							; GDT table for 32 bit
	dq 0x0
gdt_code:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0
gdt_data:
	dw 0xFFFF
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start			; Size of GDT table
	dd gdt_start					; Pointer to the start of GDT table

CODE_SEG equ gdt_code - gdt_start
DATA_SEG equ gdt_data - gdt_start

bits 32
boot32:
	mov ax, DATA_SEG
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	mov esi,hello
	mov ebx,0xb8000
.loop:
	lodsb
	and al,al
	jz .cr3
	or eax,0x0f00			; Setting text color to White
	mov word [ebx], ax
	add ebx,2
	jmp .loop
; Printing CR3 value

.cr3:
mov edi, 0xb8000 + 24		; Initializing the VGA Buffer
mov edx, 0x1f				; Initializing EDX to 31, for the index of the MSB in CR0 (it is 32 bits in size)
mov ecx, 0x0				; Initializing ECX as 0

printcr3:
	cmp edx, 0				; loop exit cond: EDX is 0
	jl finally              ; exiting loop is EDX is 0 
	mov eax, cr0			; Move value of CR0 to EAX
	mov ebx, 0				; Initializing our counter EBX to 0

	r_shift:				; right shifting to obtain desired bit
		cmp ebx, edx		; If EBX equals EDX: Break
		je next             ; Jump to print the digit
		add ebx, 1			; EBX++
		shr eax, 1			; >>1
		jmp r_shift			; loop
	next:
		and eax, 1			; last bit of EAX
		add ecx, 2			; ECX+=2
		cmp eax, 0			; If bit is 0
		je if_zero
			mov eax, 0x5f31	; Print it on the VGA as 0
			jmp if_end
		if_zero:
			mov eax, 0x5f30	; Else print it on VGA as 1
			
		if_end:
		mov [edi+ecx], eax
		sub edx, 1			; EDX--
		jmp printcr3


finally:
	cli
    hlt                     ; Halt the processor
hello: db "Hello world! ",0

times 510 - ($-$$) db 0
dw 0xaa55