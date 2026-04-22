*This project has been created as part of the 42 curriculum by **srosu**.*
# GET_NEXT_LINE

**keywords**: `Unix logic` 
**skills**: `Rigor · Unix · Algorithms & AI`


## Description

`get_next_line` is a core project of the 42 curriculum. The objective is to implement a C function that reads a file descriptor line by line, returning one line per call — including the terminating `\n` when present — and returning `NULL` once the file has been fully read or an error occurs.

The project enforces a deep understanding of:

- File descriptor I/O using the `read` syscall
- Static variable behavior across multiple function calls
- Dynamic memory allocation and deallocation without leaks
- Buffer management and string manipulation at a low level

The function must work correctly for any `BUFFER_SIZE` passed at compile time, from `1` to very large values, and handle edge cases such as empty files, files without a trailing newline, and standard input (`fd = 0`).

In addition to the files required by 42, a `main.c` is provided to make it easy to test and use the function directly from the command line.


## Key Concepts

### File Descriptors

A file descriptor (`fd`) is a small non-negative integer that the kernel assigns to an open resource — a file, a pipe, or a socket. By convention, `0` is standard input (keyboard), `1` is standard output, and `2` is standard error. When you call `open()`, the OS returns a new fd that your program uses to reference that file. All subsequent I/O operations (`read`, `write`, `close`) go through this integer. Understanding that `fd = 0` is valid and means *stdin* is critical here — a naive guard like `if (!fd)` would silently reject it.

### The `read` Syscall

`read(fd, buf, n)` asks the kernel to copy up to `n` bytes from the resource pointed to by `fd` into `buf`. It returns the number of bytes actually read, `0` at end-of-file, or `-1` on error. Because it reads in fixed-size chunks, a single `read` call may not contain a full line — or may contain several. The GNL algorithm handles this by accumulating chunks until a `\n` is found or EOF is reached.

### Static Variables

A `static` local variable is allocated once for the lifetime of the program, not on the stack frame of the function. Its value persists between calls. In GNL, `static char *stash` acts as a memory between two consecutive calls: after returning a line, whatever was read beyond the `\n` stays in the stash and is used as the starting point on the next call — without re-reading from the fd.

### Dynamic Memory & Leak Prevention

Every line returned by `get_next_line` is heap-allocated and must be freed by the caller. Internally, each `ft_strjoin` and `ft_substr` produces a new allocation, and the previous one must be freed immediately after. The most common leak in GNL is a leftover non-NULL static pointer when EOF is reached — this implementation explicitly frees and nullifies it in `update_stash`.


## How It Works

### Core Concept

The function uses a `static char *stash` variable that persists between calls. This stash accumulates data read from the file descriptor across multiple `read` calls. On each invocation of `get_next_line`, the function:

1. Reads from the file descriptor into a buffer until a newline character `\n` is found or EOF is reached, appending each chunk to the stash.
2. Extracts the first complete line (up to and including `\n` if present) from the stash.
3. Updates the stash to contain only the data that comes after the extracted line.
4. Returns the extracted line to the caller.

When the file is exhausted and the stash is empty, the function returns `NULL`.

### Internal Functions

**`read_to_stash(int fd, char *stash)`**  
Reads from `fd` in chunks of `BUFFER_SIZE` bytes and appends each chunk to the stash using `ft_strjoin`. Stops reading as soon as a `\n` is found in the accumulated stash, or when `read` returns `0` (EOF). On EOF, the stash is returned as-is so that any remaining content without a trailing newline is not lost. On a read error (`bytes_read < 0`), returns `NULL`.

**`extract(char *stash)`**  
Scans the stash for the first `\n` character and returns a substring from the beginning of the stash up to and including that `\n`. If no `\n` is found, returns the entire remaining content of the stash (the last line of a file with no trailing newline).

**`update_stash(char *stash)`**  
After a line has been extracted, advances past the `\n` and returns a new string containing only the remaining unread content. If nothing remains after the newline (or if the stash ends without a newline), frees the stash and returns `NULL`, resetting the static variable cleanly.

**`get_next_line(int fd)`**  
The main function. Validates the file descriptor, initializes the stash if needed, calls `read_to_stash`, then calls `extract` and `update_stash` in sequence. Returns the extracted line or `NULL` at end of file.

### Memory Management

A known pitfall in GNL implementations is leaving a heap-allocated empty string in the static variable after the last line is read. This causes a *reachable* memory leak reported by Valgrind. This implementation avoids it by checking `!stash[i]` in `update_stash` — when there is nothing left after the current line, the stash is freed and `NULL` is returned, so the static pointer is always `NULL` between sessions.


## File Structure

```
.
├── get_next_line.c          # Core logic
├── get_next_line_utils.c    # Helper string functions
├── get_next_line.h          # Header and BUFFER_SIZE definition
├── main.c                   # Provided for easy testing (not part of 42 submission)
└── Makefile                 # Builds a static library: gnl.a
```


## Utility Functions

The following functions are implemented from scratch in `get_next_line_utils.c`:

- `ft_strlen` — computes the length of a string
- `ft_strchr` — finds the first occurrence of a character in a string
- `ft_strjoin` — concatenates two strings into a new allocation
- `ft_strdup` — duplicates a string into a new allocation
- `ft_substr` — extracts a substring from a string given a start index and length


## Compilation & Usage

### 1. Clone the repository

```bash
git clone git@github.com:JojoShaman/get_next_line42.git
cd get_next_line42
```

### 2. Build the static library

```bash
make
```

This produces `gnl.a`, a static library containing all compiled object files.

### 3. Compile your program against the library

```bash
cc -Wall -Wextra -Werror main.c gnl.a -o GNL
```

If you want to override the buffer size at compile time:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c gnl.a -o GNL
```

### 4. Run the program

Pass the file you want to read as the first argument:

```bash
./GNL hello.txt
```

The program will print each line prefixed by its index:

```
[0] Hello, world!
[1] This is line two.
[2] No newline at end of file
```

You can also redirect the output to a file:

```bash
./GNL hello.txt > output.txt
```


## Makefile Rules

| Rule | Effect |
|------|--------|
| `make` | Compiles all sources and produces `gnl.a` |
| `make clean` | Removes all `.o` object files |
| `make fclean` | Removes `.o` files and `gnl.a` |
| `make re` | Full rebuild (`fclean` + `make`) |

---

## Edge Cases Handled

- Empty files
- Files with only newline characters
- Files without a trailing newline (last line is returned correctly)
- Very large lines or large `BUFFER_SIZE` values
- Invalid file descriptors (`fd < 0`)
- Standard input (`fd = 0`)


## Resources

### Technical Documentation

- `man 2 read` — Linux Programmer's Manual: behavior of the `read` syscall, return values, and EOF detection
- `man 3 malloc` / `man 3 free` — dynamic memory allocation and deallocation in C
- GeeksforGeeks — [Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/): explains why a `static` variable is essential to retain the stash between calls

### Articles & Guides

- Medium / 42 student write-ups (Oceano, Nikolay and others) — detailed walkthroughs of the Read → Join → Search `\n` → Split pattern that underpins GNL
- CodeQuarry — memory management in C, dangling pointers, and safe cleanup of static variables

### Testing & Debugging Tools

- **Valgrind Memcheck** — used to verify the absence of memory leaks, including *reachable* blocks left in the static variable after the last line
- **AddressSanitizer (ASan)** — Google's sanitizer built into GCC/Clang, used to catch buffer overflows and use-after-free errors at runtime (`-fsanitize=address`)
- **gnlTester** by [Tripouille](https://github.com/Tripouille/gnlTester) and **42cursus-gnl-tests** — community testers used to validate behavior across edge cases: various `BUFFER_SIZE` values, empty files, files without a trailing newline, and invalid file descriptors


## Use of AI

AI tools such as Claude were used as supplementary resources to clarify certain concepts, assist with debugging, and help with documentation.

All implementations and design choices were carried out independently.
