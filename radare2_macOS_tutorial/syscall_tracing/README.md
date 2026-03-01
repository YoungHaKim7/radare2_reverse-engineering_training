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

# DTrace Usage Guide

DTrace is a powerful dynamic tracing tool for debugging and analyzing system behavior. Here's how to use it:

## Common Patterns

### 1. List available probes
```bash
# List all probes in a provider
dtrace -l -P syscall

# List probes matching a name
dtrace -l -n 'open*'

# List probes for a specific function
dtrace -l -f malloc
```

### 2. One-liner tracing (inline scripts)
```bash
# Trace system calls (syscall entry/return)
dtrace -n 'syscall:::entry { printf("%s", probefunc); }'

# Trace process execution
dtrace -n 'proc:::exec-success { printf("%s", curpsinfo->pr_psargs); }'

# Count system calls by name
dtrace -n 'syscall:::entry { @calls[probefunc] = count(); }'
```

### 3. Trace a running process
```bash
# Attach to PID 1234
dtrace -p 1234 -n 'syscall:::entry { printf("%s", probefunc); }'

# Trace a specific command
dtrace -c 'ls -la' -n 'syscall:::entry { printf("%s", probefunc); }'
```

### 4. Use a script file
```bash
dtrace -s script.d
```

### 5. Output to file
```bash
dtrace -o trace.log -n 'syscall:::entry { printf("%s", probefunc); }'
```

## Probe Syntax

```
provider:module:function:name
/ predicate /
{ action }
```

**Example:**
```d
syscall::open*:entry   # provider=syscall, function=open*, name=entry
/fd->fs_path == "foo"/  # predicate: only match when path equals "foo"
{ printf("opened %s", copyinstr(fd->fs_path)); }  # action
```

## Common Providers

| Provider | Description |
|----------|-------------|
| `syscall` | System calls |
| `proc` | Process lifecycle events |
| `io` | I/O events |
| `sched` | CPU scheduling |
| `profile` | Timer-based profiling |

## Quick Reference

```bash
# Count syscalls by process name
dtrace -n 'syscall:::entry { @[execname] = count(); }'

# Trace files opened by a process
dtrace -n 'syscall::open*:entry { printf("%s %s", execname, copyinstr(arg0)); }'

# Profile stack traces at 997Hz
dtrace -n 'profile:::profile-997 /pid == $target/ { @[ustack()] = count(); }' -p <PID>
```

Would you like me to help with a specific tracing scenario for your radare2 reverse engineering work?
