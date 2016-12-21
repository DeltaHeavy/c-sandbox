# source http://weeb.ddns.net/0/programming/c_without_standard_library_linux.txt

# refer to https://software.intel.com/sites/default/files/article/402129/
# mpx-linux64-abi.pdf

first:
	gcc -O0 -g hello.c
	# gdb: set backtrace past-main on
	# 	set backtrace past-entry on
	# 	bt
	# 	Notice: _start __libc_start_main
second:
	gcc -s -O2 hello.c
	# wc -c a.out
	# Notice: it's huge, even with optimizations
third:
	gcc -s -O2 -nostdlib hello.c
	# no _start, missing puts
fourth:
	gcc puts.c
	# strace
	# Notice: write syscall
fifth:
	gcc -s -O2 -nostdlib write.c
	# no _start, missing write
sixth:
	gcc -s -O2 -nostdlib hello.S hello_s.c
	# no _start
	# _start needs to:
	# 	zero rbp
	# 	put argc into rdi
	# 	put the stack address of argv[0] into rsi
	# 	align the stack to 16 bytes
	# 	call main
seventh:
	gcc -s -O2 -nostdlib hello_start.S hello_s.c
	# YAY! ^_^
	# segfault -_-
	# Why? because ret in _start doesn't make sense
eighth:
	gcc -s -O2 -nostdlib hello_start_exit.S hello_s.c
	# WOOT! Also, wc -c shows it's much smaller
ninth:
	gcc -s -O2 -nostdlib -fno-unwind-tables -fno-asynchronous-unwind-tables hello_start_exit.S hello_s.c
	# unwind tables are used for exception handling
	# wc -c: even smaller!
	# objdump -x a.out
	# objdump -s -j .comment a.out
	# strip -R .comment a.out
	# strip -R .note.gnu.build-id a.out
	# wc -c: even smaller!
final:
	./build.sh
	# larger, due to syscall0-5, but slightly faster due to nixing extra movs
	# cleaner, using some preprocessing
