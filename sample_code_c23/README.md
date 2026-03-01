# `strace`

```bash
 strace ./target/a01_write_gdb
execve("./target/a01_write_gdb", ["./target/a01_write_gdb"], 0x7ffeafc8ff10 /* 69 vars */) = 0
brk(NULL)                               = 0x17390000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3bf5650000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=104703, ...}) = 0
mmap(NULL, 104703, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7f3bf5636000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libm.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\0\0\0\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1117776, ...}) = 0
mmap(NULL, 1027168, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f3bf553b000
mmap(0x7f3bf554c000, 552960, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x11000) = 0x7f3bf554c000
mmap(0x7f3bf55d3000, 393216, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x98000) = 0x7f3bf55d3000
mmap(0x7f3bf5633000, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0xf7000) = 0x7f3bf5633000
close(3)                                = 0
openat(AT_FDCWD, "/lib64/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0\16\265\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 840, 64) = 840
fstat(3, {st_mode=S_IFREG|0755, st_size=2424320, ...}) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 840, 64) = 840
mmap(NULL, 2127216, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x7f3bf5200000
mmap(0x7f3bf5228000, 1540096, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x7f3bf5228000
mmap(0x7f3bf53a0000, 339968, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1a0000) = 0x7f3bf53a0000
mmap(0x7f3bf53f3000, 53248, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1f2000) = 0x7f3bf53f3000
mmap(0x7f3bf5400000, 30064, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f3bf5400000
close(3)                                = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f3bf5539000
arch_prctl(ARCH_SET_FS, 0x7f3bf553a0c0) = 0
set_tid_address(0x7f3bf553a390)         = 9969
set_robust_list(0x7f3bf553a3a0, 24)     = 0
rseq(0x7f3bf553a000, 0x20, 0, 0x53053053) = 0
mprotect(0x7f3bf53f3000, 16384, PROT_READ) = 0
mprotect(0x7f3bf5633000, 4096, PROT_READ) = 0
mprotect(0x403000, 4096, PROT_READ)     = 0
mprotect(0x7f3bf5691000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
getrandom("\x8f\x1f\x3f\x73\x8a\xe5\x0f\x20", 8, GRND_NONBLOCK) = 8
munmap(0x7f3bf5636000, 104703)          = 0
write(1, "HACK\n", 5HACK
)                   = 5
exit_group(0)                           = ?
+++ exited with 0 +++
```
