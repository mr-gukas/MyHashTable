section .text
global rolHash_asm

rolHash_asm:
    push rbx 
    push rcx

    xor     eax, eax        ; Обнуляем eax (регистр для хеша)
    xor     ecx, ecx        ; Обнуляем ecx (регистр для индекса)
.loop:
    mov     bl, byte [rdi + rcx]    ; Загружаем очередной байт строки в bl
    test    bl, bl                  ; Проверяем, не кончилась ли строка
    jz      .end_loop               ; Если кончилась, выходим из цикла
    rol     eax, 1                  ; Сдвигаем хеш влево на 1 бит
    xor     al, bl                  ; XOR-им байт строки с младшим байтом хеша
    inc     ecx                     ; Увеличиваем индекс
    jmp     .loop                   ; Переходим на следующую итерацию цикла
.end_loop:
    pop rcx 
    pop rbx
    ret                             ; Возвращаем результат в eax

