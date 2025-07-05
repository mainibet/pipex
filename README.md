# Pipex

Pipex is a C program designed to replicate the functionality of shell piping (`|`) and input/output redirection (`<`, `>`). 
It takes an input file, two commands, and an output file as arguments, executing the first command with the input file as its standard input and 
piping its output to the second command, which then writes its standard output to the specified output file.

## Table of Contents

- [About the Project](#about-the-project)
- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Building the Project](#building-the-project)
- [Contributing](#contributing)
- [License](#license)
- [Contact](#contact)
- [Acknowledgments](#acknowledgments)

## About the Project

This project implements a simplified version of the shell's piping mechanism. It demonstrates the use of fundamental Unix system calls such as
`fork()`, `pipe()`, `dup2()`, `execve()`, and `waitpid()` to manage processes, inter-process communication, and I/O redirection. 
The program is robust, including error handling for file operations, command execution, and system call failures. 
It also handles command path resolution using the `PATH` environment variable.

The project utilizes the **libft** library, a custom C library with various utility functions, which is included as a submodule.

## Features

- **Pipe Implementation**: Connects the standard output of the first command to the standard input of the second command.
- **Input Redirection**: Reads input for the first command from a specified input file.
- **Output Redirection**: Writes the output of the second command to a specified output file.
- **Command Execution**: Executes external commands using `execve()`.
- **Path Resolution**: Automatically finds the full path of commands using the `PATH` environment variable.
- **Error Handling**: Includes robust error checking for file opening, piping, forking, and command execution, providing informative error messages.
- **Process Management**: Manages child processes using `fork()` and `waitpid()`.

## Getting Started

To get a local copy of Pipex up and running, follow these simple steps.

## Getting Started

To get a local copy of Pipex up and running, follow these simple steps.

### Prerequisites

* A C compiler (e.g., `gcc`, `clang`)
* `make` utility
* `git` (to clone the repository)

### Installation

**Clone the repo**:

```bash
git clone [https://github.com/mainibet/pipex.git](https://github.com/mainibet/pipex.git)
cd pipex
```
**Built the project**:
The Makefile will automatically build libft as a prerequisite.

```make```

**Run with arguments**

The pipex program expects exactly four arguments: an input file, the first command, the second command, and an output file.

```
./pipex <infile> <cmd1> <cmd2> <outfile>
```
**Arguments**:

- `<infile>`: The path to the input file for cmd1.
- `<cmd1>`: The first command to be executed. This command's output will be piped to cmd2.
- `<cmd2>`: The second command to be executed. This command will receive input from cmd1 and write its output to `<outfile>`.
- `<outfile>`: The path to the output file where cmd2's output will be written. If the file exists, it will be truncated; otherwise, it will be created.

**Example**:

To replicate cat infile | grep "hello" > outfile:

### Error Handling:

- The program will print error messages to stderr if:
- The number of arguments is incorrect.
- The input file cannot be opened or read.
- A command is not found or is not executable.
- System calls like pipe(), fork(), dup2(), or execve() fail.

## Building the Project

The project uses a Makefile for compilation and management.

- **make all (or just make)**: Compiles the source files and links them with libft to create the pipex executable.

- **make clean**: Removes all object files (.o).

- **make fclean**: Removes all object files (.o) and the pipex executable.

- **make re**: Performs a fclean followed by an all, effectively recompiling the entire project from scratch.

The libft library, located in the libft subdirectory, is automatically built by the pipex Makefile if it hasn't been built already.

## 🗂️ File Structure
```
.
├── Makefile
├── pipex.c
├── pipex.h
├── libft/
│   └── (libft files and directories)
├── util_child.c
├── util_exec.c
├── util_findpath.c
├── util_initial.c
├── util_other.c
└── util_parent.c

```
## Contributing
Any contributions you make are greatly appreciated.

If you have a suggestion that would make this better, please fork the repo and create a pull request.

##  Autor
Alicia Betancourt ([mainibet](https://github.com/mainibet))

## Acknowledgments
This project was developed as part of the 42 Berlin curriculum.

Thanks to the previous libft project for providing essential utility functions.



