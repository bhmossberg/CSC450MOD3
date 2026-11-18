# CSC450MOD3 – Pointers and Dynamic Memory in C++

A C++ program that reads three integers, copies each one to the heap with `new`, prints the stack value, the pointer address and the value it points to, and then frees the memory with `delete`. Input and allocation failures are handled safely.

## Overview

This is **CSU Global CSC450, Module 3 (Critical Thinking)**. The repository is an Eclipse workspace folder with one **Eclipse CDT** project (`CSC450_Mod3_CT_Mossberg/`, MinGW GCC toolchain). The source is `src/CSC450_Mod3_CT_Mossberg.cpp`, documented with Doxygen comments.

## How the code works

| Function | Purpose |
|---|---|
| `bool readInt(const char* label, int& out)` | Prints the prompt and reads with `std::cin >> out`. If the read fails, it calls **`cin.clear()`** to reset the fail bit and **`cin.ignore(numeric_limits<streamsize>::max(), '\n')`** to discard the bad line, then returns `false`. The output parameter is passed **by reference**. |
| `void show(const char* name, int value, const int* ptr)` | Prints `name variable = value, pointer address = ptr, pointed-to value = *ptr`. The value is passed **by value** (a copy) and the heap copy through a pointer to `const`. |
| `int main()` | Reads `a`, `b` and `c`. If any read fails, it exits with code `1` **before allocating anything**. It then allocates `pa = new int(a)` (and the same for `b` and `c`) inside `try`. If `std::bad_alloc` is thrown, it deletes any pointers already allocated (they start as `nullptr`, and deleting `nullptr` is safe) and exits with code 1. On success it prints all three, deletes each pointer, and sets each one back to `nullptr`. |

The design follows simple memory-safety rules: initialize pointers to `nullptr`, free every allocation on both the success and failure paths, null pointers after `delete`, and never read input you haven't validated.

## Build and run

Any C++11 compiler:

```bash
g++ -std=c++11 -o heapcopy CSC450_Mod3_CT_Mossberg/src/CSC450_Mod3_CT_Mossberg.cpp
./heapcopy
```

Sample run (verified; addresses differ on every run):
```
Enter first integer: 7
Enter second integer: -3
Enter third integer: 42
Stack variables and heap copies:
a variable = 7, pointer address = 0x2a8f92c0, pointed-to value = 7
b variable = -3, pointer address = 0x2a8f92e0, pointed-to value = -3
c variable = 42, pointer address = 0x2a8f9300, pointed-to value = 42
```

Invalid input (`abc`) prints `Input was not a valid integer. No heap allocation performed.` and exits with status 1.

`system("pause")` keeps the Windows console open; on Linux or macOS it only prints a harmless "not found" message.

## Concepts demonstrated
- Stack and heap storage, and `new`/`delete`
- Pointers: printing addresses and dereferencing
- Pass by value, pass by reference and pointer to `const`
- Exception handling for `std::bad_alloc`
- Recovering the input stream after a failure (`clear`/`ignore`)
- Preventing memory leaks and dangling pointers
