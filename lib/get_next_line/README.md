# get_next_line

get_next_line is a project developed for 42 Heilbroon School.

## Keywords
C programming - read() - file descriptor - buffer - static variable

## Subject
In this project I had to create a function which `read()` from a text file everytime is called, line by line. For more info about the requirements, take a look at the [subject](en.subject.pdf) contained in this repo.

## Brief explanation
The project covers the following topics:

### 1. Static variable
As suggested by the subject, the use of a static variable `static char *line` is a way to remember the line returned every time the function is called. Their use involve static memory allocation, which extends their lifetime through the entire run of the program.

### 2. Buffer
To properly use `read()` it is necessary to understand this basic concept. In general, a buffer is a temporary storage area, where the data is hold to be moved, processed or transferred (think about the data transferred in a video streaming service).

### 3. Leaks free
Like in any other project of 42, the memory allocated by `malloc()` has to be properly sfreed. No leaks are tolerated. In this project I checked the leaks using [valgrind](https://valgrind.org/) and `system("leaks <program-name>")`

## Bonus
In the bonus part of the project the goal is implement a version of `get_next_line` which can manage multiple file descriptors at the same time remembering the current line of each file, so that everytime the function is called, returns the correct next line of each one.

---

## Try it out
1. Clone the repository:
```
git clone git@github.com:NicoCastelnuovo/get_next_line.git get_next_line
```
2. Navigate to the `get_next_line` directory and `make` the archive, or `make bonus` for more funcionalities:
```
cd get_next_line
make
```
3. To use the function in inside your .c file, you have to include the header on the top of it:
```
#include "get_next_line.h"
```
4. Compile your executable. you can add the optional argument `-D BUFFER_SIZE=n` to change the size of the buffer which `read()` uses to read from the file:
```
cc <your_main.c> ./<gnl_path>/libgnl.a -I ./<gnl_path>/get_next_line.h -o <program_name> [-D BUFFER_SIZE=n]
```
> **Note:** if you need to `open()` the file and `read()`, remember to `# include <fcntl.h>` header inside your project!

5. Enjoy!
