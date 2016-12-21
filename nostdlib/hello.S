/* intel syntax without % prefix for registers */
.intel_syntax noprefix

.text
    .globl syscall5

    syscall5:
        mov rax,rdi /* assign func param 1 */
        mov rdi,rsi /*   "     "    "    2 */
        mov rsi,rdx /*   "     "    "    3 */
        mov rdx,rcx /*   "     "    "    4 */
        mov r10,r8  /*   "     "    "    5 */
        mov r8,r9   /*   "     "    "    6 */
        syscall
        ret

