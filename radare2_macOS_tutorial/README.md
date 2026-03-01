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
