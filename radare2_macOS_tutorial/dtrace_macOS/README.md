Yes, on macOS the alternative to `strace` is `dtruss` (which uses DTrace underneath).

## Equivalent commands:

**Instead of:**
```bash
strace ./target/a01_write_strace_radare2
```

**Use on macOS:**
```bash
sudo dtruss ./target/a01_write_strace_radare2
```

## Other options:

| Command | Description |
|---------|-------------|
| `sudo dtruss ./program` | Most strace-like output |
| `sudo dtrace -n 'syscall:::entry { printf("%s", probefunc); }'` | Raw DTrace |
| `instruments -t syscalls ./program` | GUI tool (requires Xcode) |

## Key differences:

- `dtruss` requires `sudo` on macOS (SIP may need to be partially disabled for full tracing)
- Output format is slightly different from strace
- Some system calls have different names on macOS (BSD vs Linux)

For a quick trace similar to strace, `dtruss` is your best bet.
