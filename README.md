# Lab 9 — System Calls  
**Course:** CPE 2600 – Systems Programming  
**Author:** Jesse Rost  
**Section:** 112  
**Date:** November 2, 2025  

---

## Overview
This lab explores several commonly used **POSIX system calls** across different categories:
- **Information Maintenance**
- **Process Control**
- **Process Modification**
- **File Management**

The purpose of these programs is to gain hands-on experience interfacing directly with the operating system’s kernel-level services rather than using higher-level library abstractions.

Each source file demonstrates a specific set of system calls and concepts.

---

## Building the Programs
A `Makefile` is included for easy compilation.

To build all executables:
```bash
make all
