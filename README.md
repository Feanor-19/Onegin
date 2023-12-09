# Onegin
Educational project at MIPT. A library for convenient reading from files and my implementation of quicksort.

## Brief description
`Onegin` is not only a `novel in verse`, but also a library for reading from files and moreover a program, which is capable of reading a file (for example, containing Pushkin's novel), sorting it's 
lines in some specific way and writing the result in a different file.

## Program usage
### Command line flags
1. `-tests` Runs tests for custom implementation of quicksort.
2. `-fin` Specifies input file.
3. `-out` Specifies output file.
4. `-addr` Turns on printing addresses of sorted strings (used in educational purposes).
5. `-sb` Specifies to sort by beginnings of lines.
6. `-se` Specifies to sort by ends of lines.
### Examples
In the root folder you can find:
- `Onegin.txt`, which is the original text.
- `sb.txt`, which is the lines of the original text, sorted by beginnings. So, it looks like an encyclopedia! Just as Belinsky once said: `Onegin is the encyclopedia of the russian life`.
- `seee.txt`, which is the lines of the original text, sorted by ends. It ignores punctuation symbols, so the resulting lines are kind of rhymed!
## Library usage
Because it is one of the first educational projects at MIPT, it is not quite formed as a library, but it is easy to understand what each function does, so you can use it in your projects.
For example, `read_file_to_buf` does just what it says, returning struct FileBuf, which contains pointer to dynamically allocated string, containing the whole file.
