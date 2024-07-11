# UWE exercise

This repository contains a very simple example program that aims 
to practice software security, particularly dynamic program analysis 
and data flow integrity (DFI). This example does not require and 
support static analysis, which is commonly adopted for DFI.

The examples included are listed below. It is recommended to understand
`corrupted.c` to complete `instrumented.c` (task):

 - `corrupted.c`: this unsafe reference code demonstrates vulnerabilities - 
   local variables and return address are corrupted by buffer overflow. 
 - `instrumented.c`: this file contains an incomplete instrumented version
    of `corrupted.c`, which students should complete. See the comments 
    in the file for details of the task.
 - `libutil.c`: this is for a shared library, which both corrupted.c and
    instrumented.c use. Students do not need to touch this file.
 - `foo.txt`: an input file to corrupted.c and instrumented.c, which contains
    a string.

## How to build

Prerequisites:

 - GCC toolchain. (Clang may crash.)
 - Bash 5.x and Make 4.x.

To compile and link the examples, run make:

    make

The main entry point for the build is the `makefile` in the project root.
All sources are located under the `src` directory and are further grouped
into folders including an unsafe reference program and task program. 

Note that students must enable "exercise.make" in the `makefile` to 
build the exercise (instrumented.c). 

To test, use:

    make test

## How to run

All the example applications are intended to be used on Linux userspace. 
A reference program (`dfi`) will be created under build/bin folder.
The task program will be created in the same folder (`exercise`).


