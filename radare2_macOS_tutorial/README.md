**Static analysis works!** You can see the disassembly of your binary showing the `write(1, "HACK\n", 5)` call.

## Summary - For actual debugging (`r2 -d`), you need to:

### Easiest Solution - Disable SIP:
```bash
# 1. Shut down Mac
# 2. Hold Power button until "Loading startup options" appears
# 3. Click Options, select your volume, click Continue
# 4. Open Terminal from Utilities menu
# 5. Run: csrutil disable
# 6. Reboot
```

After disabling SIP, radare2's debugger will work.

### Alternative - Use lldb (Apple's debugger):
```bash
lldb ./target/a01_write_strace_radare2
(lldb) b main
(lldb) run
(lldb) disas
```

### Static Analysis - Works Now:
```bash
radare2 ./target/a01_write_strace_radare2
[0x1000005b0]> aaa          # analyze all
[0x1000005b0]> pdf @ main   # disassemble main
[0x1000005b0]> afl          # list functions
[0x1000005b0]> izz          # list strings
```

**Bottom line**: macOS M1's security prevents ptrace debugging unless SIP is disabled or you use a properly self-built and signed radare2. Static analysis works fine.


```bash
[0x1000005c8]> pdf
            ;-- section.0.__TEXT.__text:
            ;-- entry0:
            ;-- func.1000005b0:
            ;-- dbg.main:
            ;-- pc:
            ; NULL XREF from aav.0x100000020 @ +0xb0(r)
┌ 40: int main (int argc, char **argv, char **envp);
│ afv: vars(2:sp[0x8..0x10])
│           0x1000005b0 b    fd7bbfa9       stp x29, x30, [sp, -0x10]! ; main.c:3:16int main(void) { write(1, "HACK\n", 5); } ; int main();
│           0x1000005b4      fd030091       mov x29, sp
│           0x1000005b8      a20080d2       mov x2, 5                  ; main.c:3:18int main(void) { write(1, "HACK\n", 5); } ; size_t nbytes
│           0x1000005bc      00000090       adrp x0, sym.__mh_execute_header ; 0x100000000 ; int fd
│           0x1000005c0      01a01791       add x1, x0, 0x5e8          ; 0x1000005e8 ; "HACK\n" ; const char *ptr
│           0x1000005c4      20008052       mov w0, 1
│           0x1000005c8 b    04000094       bl sym.imp.write           ; ssize_t write(int fd, const char *ptr, size_t nbytes)
│           0x1000005cc      00008052       mov w0, 0
│           0x1000005d0      fd7bc1a8       ldp x29, x30, [sp], 0x10   ; main.c:3:41int main(void) { write(1, "HACK\n", 5); }
└           0x1000005d4      c0035fd6       ret
[0x1000005c8]> pdf @ main
            ;-- section.0.__TEXT.__text:
            ;-- entry0:
            ;-- func.1000005b0:
            ;-- dbg.main:
            ;-- pc:
            ; NULL XREF from aav.0x100000020 @ +0xb0(r)
┌ 40: int main (int argc, char **argv, char **envp);
│ afv: vars(2:sp[0x8..0x10])
│           0x1000005b0 b    fd7bbfa9       stp x29, x30, [sp, -0x10]! ; main.c:3:16int main(void) { write(1, "HACK\n", 5); } ; int main();
│           0x1000005b4      fd030091       mov x29, sp
│           0x1000005b8      a20080d2       mov x2, 5                  ; main.c:3:18int main(void) { write(1, "HACK\n", 5); } ; size_t nbytes
│           0x1000005bc      00000090       adrp x0, sym.__mh_execute_header ; 0x100000000 ; int fd
│           0x1000005c0      01a01791       add x1, x0, 0x5e8          ; 0x1000005e8 ; "HACK\n" ; const char *ptr
│           0x1000005c4      20008052       mov w0, 1
│           0x1000005c8 b    04000094       bl sym.imp.write           ; ssize_t write(int fd, const char *ptr, size_t nbytes)
│           0x1000005cc      00008052       mov w0, 0
│           0x1000005d0      fd7bc1a8       ldp x29, x30, [sp], 0x10   ; main.c:3:41int main(void) { write(1, "HACK\n", 5); }
└           0x1000005d4      c0035fd6       ret
[0x1000005c8]> afl
0x1000005d8    1     16 sym.imp.write
0x1000005b0    1     40 main
[0x1000005c8]> izz
nth paddr      vaddr       len size section            type  string
―――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
0   0x00000028 0x00000028  10  11                      ascii __PAGEZERO
1   0x00000070 0x00000070  6   7                       ascii __TEXT
2   0x000000b0 0x000000b0  6   7                       ascii __text
3   0x000000c0 0x000000c0  6   7                       ascii __TEXT
4   0x00000100 0x00000100  7   8                       ascii __stubs
5   0x00000110 0x00000110  6   7                       ascii __TEXT
6   0x00000150 0x00000150  9   10                      ascii __cstring
7   0x00000160 0x00000160  6   7                       ascii __TEXT
8   0x000001a0 0x000001a0  10  11                      ascii __eh_frame
9   0x000001b0 0x000001b0  6   7                       ascii __TEXT
10  0x000001f8 0x000001f8  12  13                      ascii __DATA_CONST
11  0x00000238 0x00000238  5   6                       ascii __got
12  0x00000248 0x00000248  12  13                      ascii __DATA_CONST
13  0x00000290 0x00000290  10  11                      ascii __LINKEDIT
14  0x00000364 0x00000364  13  14                      ascii /usr/lib/dyld
15  0x000003f0 0x000003f0  26  27                      ascii /usr/lib/libSystem.B.dylib
16  0x0000041c 0x0000041c  12  13                      ascii @loader_path
17  0x0000043c 0x0000043c  79  80                      ascii /opt/homebrew/Cellar/gcc/15.2.0_1/lib/gcc/current/gcc/aarch64-apple-darwin25/15
18  0x0000049c 0x0000049c  53  54                      ascii /opt/homebrew/Cellar/gcc/15.2.0_1/lib/gcc/current/gcc
19  0x000004e4 0x000004e4  17  18                      ascii /opt/homebrew/lib
20  0x00000504 0x00000504  21  22                      ascii /opt/homebrew/include
21  0x0000052c 0x0000052c  49  50                      ascii /opt/homebrew/Cellar/gcc/15.2.0_1/lib/gcc/current
22  0x000005e8 0x1000005e8 5   6    2.__TEXT.__cstring ascii HACK\n
23  0x00008055 0x100008055 6   7                       ascii _write
24  0x00008074 0x100008074 18  19                      ascii _mh_execute_header
25  0x00008087 0x100008087 5   6                       ascii \tmain
26  0x00008164 0x100008164 17  18                      ascii mh_execute_header
27  0x00008176 0x100008176 5   6                       ascii _main
28  0x0000817c 0x10000817c 6   7                       ascii _write
29  0x00008183 0x100008183 120 121                     ascii /Users/gy-gyoung/my_project/C_lang/radare2_reverse-engineering_training/radare2_tutorial/a01_write_strace_radare2/./src/
30  0x000081fc 0x1000081fc 6   7                       ascii main.c
31  0x00008203 0x100008203 60  61                      ascii /var/folders/10/fq530b312d1ctnl93d0qbwc40000gn/T//cc758eZW.o
32  0x000082ac 0x1000082ac 24  25                      ascii a01_write_strace_radare2
33  0x000082c5 0x1000082c5 4   6                       utf8  [Gƽ4
34  0x000082ce 0x1000082ce 5   6                       ascii $uyOd
35  0x000083d6 0x1000083d6 4   5                       ascii *0;b
[0x1000005c8]>
```
