section .text
global my_strcmp

my_strcmp:
    xor rax, rax ; clear the return value

.loop:
    mov al, byte [rdi] 
    cmp al, byte [rsi] 
    jne .done 
    inc rdi 
    inc rsi 
    test al, al 
    jnz .loop  

.equal:
    mov rax, 0  
    ret

.done:
    movzx eax, byte [rdi] 
    sub eax, dword [rsi] 
    ret

