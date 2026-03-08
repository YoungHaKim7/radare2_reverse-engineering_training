# Result

```bash
$ /opt/homebrew/opt/gcc@15/bin/gcc-15 -std=c23 -pedantic -pthread -pedantic-errors -lm -Wall -Wextra -ggdb -Werror -o ./target/a02_mem_io_out ./src/main.c

$ ./target/a02_mem_io_out test.txt
Usage: ./target/a02_mem_io_out <source_file> <dest_file>

$ ./target/a02_mem_io_out test.txt out.txt
page_size : 16384
```

# 실행
- The program now shows a proper usage message. The code expects two arguments: a source file and a destination file for memory-mapped copying.

Would you like me to:
1. Create test files for demonstration?
2. Modify the `just r` recipe to include default test arguments?

For example, I could create a simple test setup that:
- Creates a source file with some content
- Runs the program to copy it via mmap
- Shows the result

Let me know how you'd like to proceed!
