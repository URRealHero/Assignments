.686P
.model flat, stdcall
  ExitProcess proto :dword
  includelib  kernel32.lib
  includelib  libcmt.lib
  includelib  legacy_stdio_definitions.lib
  putchar     proto c :byte  ;	显示给定 ASCII 对应的字符
.stack 200
.data
  ret_address dword 0
.code
main proc c 
     push  offset msg1
     mov   ret_address, offset L1
     jmp  display
msg1 db 'Very Good',0DH,0AH,0

L1:  
     push  offset msg2
     mov   ret_address, offset L2
     jmp  display
msg2 db '12345',0DH,0AH,0

L2:  invoke ExitProcess, 0
     ret
main endp
; _________________________________
; 显示一个字符串 
display proc
   pop  ebx
p1:
   cmp  byte ptr [ebx],0
   je   exit
   invoke  putchar, byte ptr [ebx] 
   inc  ebx
   jmp  p1
exit:
   jmp  ret_address
display endp

end