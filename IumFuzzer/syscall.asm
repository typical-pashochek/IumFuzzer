OPTION DOTNAME
.code

sys_call PROC
    mov r10, rcx
    mov eax, 8000007h
    syscall
    ret

sys_call ENDP
END sys_call
