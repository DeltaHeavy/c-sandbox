#!/bin/sh

exename="hello"

# -Wl, --gc-sections   : remove unused code sections
# -fdata-sections      : separate functions into code sections to enable above
# -fno-stack-protector : no extra code to guard against overflows
# -Wa, --noexecstack   : mark stack memory non-executable
# -fno-builtin         : disable all builtin functions

gcc -std=c89 -pedantic -s -O2 -Wall -Werror \
   -nostdlib \
   -fno-unwind-tables \
   -fno-asynchronous-unwind-tables \
   -fdata-sections \
   -Wl,--gc-sections \
   -Wa,--noexecstack \
   -fno-builtin \
   -fno-stack-protector \
   hello_start_exit_params.S hello_s_params.c \
   -o $exename \
\
&& strip -R .comment $exename \
&& strip -R .note.gnu.build-id $exename
