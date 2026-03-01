On macOS, to trace syscalls with **Instruments**:

## Using Xcode Instruments

```bash
# Launch Instruments from command line
open -a "Instruments"
```

Then:
1. File → New → **System Trace** template
2. Choose your target process
3. Click record

## Quicker Command-Line Options

For syscall tracing specifically, `dtruss` is often more convenient:

```bash
# Trace a specific command
sudo dtruss your-command

# Trace by PID
sudo dtruss -p <pid>

# Filter specific syscalls (e.g., open, read, write)
sudo dtruss -t open your-command
```

Or use `dtrace` directly:

```bash
# Simple syscall trace
sudo dtrace -n 'syscall:::entry { printf("%s", probefunc); }'

# With timestamps
sudo dtrace -n 'syscall:::entry { printf("%Y %s", timestamp, probefunc); }'
```

Given your radare2 training context, are you looking to trace the `src/main.c` binary you've been working on?
