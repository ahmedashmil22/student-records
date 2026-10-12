# Student Records Manager

A small command-line program in C that I built to practise C fundamentals: structs, pointers, arrays, file handling and input validation. You can add, search and delete student records, and everything is saved to a file so it's still there the next time you run it.

## What it can do
- Add a student (id, name, marks), and it won't accept an id that already exists
- List all students
- Search for a student by id
- Delete a student by id
- Save to `students.txt` after every action and load it again on startup

## How to run it
```
gcc -Wall -Wextra -g main.c -o records
./records
```
On Windows PowerShell, use `.\records.exe` instead of `./records`.

## How it works
- Students are stored in an array of structs, with room for 100.
- `add_student` and `delete_student` take the student count as a pointer, because they need to change it in `main`. `list_students` and `find_student` only read it, so they take a plain `int`.
- `find_student` returns the position of the student in the array, or `-1` if the id isn't there. `delete_student` uses that position and shifts the later students one slot to the left.
- I check the return values of `scanf`, `fscanf` and `fopen`, and read names with `%49s` so a long name can't overflow the buffer.
- The save file is plain text. The first line is the number of students, then one student per line (`id name marks`).
- When loading, the count from the file is checked against the array size, so a damaged file can't write past the end of the array.

## Known limitations
- Names have to be a single word, because `%s` stops at a space.
- It's capped at 100 students, since the array has a fixed size.
- If you type a letter where a number is expected, the program exits.

## What I'd improve next
- Use `malloc` and `realloc` so the list can grow instead of stopping at 100
- Use `fgets` so names can contain spaces
- Split the code into `student.h`, `student.c` and `main.c`, with a Makefile
- Add some tests

## What I learned
Most of my bugs came from small details: using `%.2f` in `scanf`, comparing the index to `1` instead of `-1`, and forgetting `&` for a `float`. Compiling with `-Wall -Wextra` and tracing a small example by hand helped me find them.