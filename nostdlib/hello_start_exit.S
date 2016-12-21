/* intel syntax without % prefix for registers */
.intel_syntax noprefix

.text
    .globl _start, syscall5

    _start:
        xor rbp,rbp
        pop rdi /* rdi = argc, adds 8 to rsp */
        mov rsi,rsp /* rest of stack as argv */

        and rsp,-16 /* zeroes the lowest 4 bits of rsp, aligning to 16 bytes */
        call main

        mov rdi,rax /* get syscall result */
        mov rax,60 /* syscall number for _exit */
        syscall

        ret /* never reached */

    syscall5:
        mov rax,rdi /* assign func param 1 */
        mov rdi,rsi /*   "     "    "    2 */
        mov rsi,rdx /*   "     "    "    3 */
        mov rdx,rcx /*   "     "    "    4 */
        mov r10,r8  /*   "     "    "    5 */
        mov r8,r9   /*   "     "    "    6 */
        syscall
        ret

