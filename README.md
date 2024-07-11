# UWE exercise

This repository contains naive example programs that aim 
to practice software security, particularly dynamic program analysis 
and data flow integrity (DFI). The examples do not require and 
support static analysis, which is commonly adopted for DFI.

All sources are located under the [src](src/) directory and are further grouped
into folders including an unsafe reference program and task program. 

The examples included are listed below. It is recommended to understand
`corrupted.c` for a task, which is to complete `instrumented.c`:

 - `corrupted.c`: this unsafe reference code demonstrates vulnerabilities - 
   local variables and return address are corrupted by buffer overflows.
   As a result, the control flow of the program is affected by corrupted
   control data (return address) and non-control data (local variables).  
 - `instrumented.c`: this file contains an incomplete instrumented version
    of `corrupted.c`, which students should complete. See the comments 
    in the file for more details of the task.
 - `libutil.c`: this is for shared library, which both `corrupted.c` and
    `instrumented.c` use. Students do not need to touch this file.
 - `foo.txt`: an input file to `corrupted.c` and `instrumented.c`, which contains
    a string.

## Reference 

Securing software by enforcing data-flow integrity
[Securing software by enforcing data-flow integrity](https://www.microsoft.com/en-us/research/wp-content/uploads/2006/11/dfiOSDI.pdf)

## How to build

Prerequisites:

 - GCC toolchain. (Clang may crash.)
 - Bash 5.x and Make 4.x.

To compile and link the examples, run make:

    make

The main entry point for the build is the `makefile` in the project root.
Note that students must enable `exercise.make` in the `makefile` to 
build the exercise (`instrumented.c`). 

To test, use:

    make test

## How to run

All the example applications are intended to be used on Linux userspace. 
A reference program (`dfi`) will be created under build/bin folder.
The task program will be created in the same folder (`exercise`), once
the code being completed correctly.


