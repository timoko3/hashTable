default rel
section .text

global _start
global optimizedStrcmp

_start:
    lea rdi, [str1]
    lea rsi, [str2]
    call optimizedStrcmp

optimizedStrcmp:
    vmovdqu8 zmm0, [rdi]
    vmovdqu8 zmm1, [rsi]

    mov rax, 1d

    vpcmpub k1, zmm0, zmm1, 0

    kortestq k1, k1  
    jnc notEqual
        mov rax, 0d
    notEqual:



    ret

str1 db "testasdfadsfasdfasdvabadbbfbgbfgbgfbdfbdfgbfdbdfgbdfgbdfgbdfgbdfgfdvdfvdfgbfgvfvdfbg", 0h
str2 db "testasdfadsfasdfasdvabadbbfbgbfgbgfbdfbdfgbfdbdfgbdfgbdfgbdfgbdfgfdvdfvdfgbfgvfvdfbg", 0h
