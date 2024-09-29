# MY SHELL

  

## Overview

This program is a simplified version of a Unix shell. It supports the execution of both built-in commands and external commands available on the system. The shell uses the execve() system call to execute external commands and provides functionality for basic shell operations through its own built-in commands.
  

## Features

The shell supports the following built-in commands: <br  />

  

``[echo]`` - Displays a line of text or the value of a variable. <br  />

``[cd]`` - Changes the current directory. <br  />

``[setenv] ``- Sets an environment variable. <br  />

``[unsetenv]`` - Unsets an environment variable. <br  />

``[env]`` - Displays the current environment variables. <br  />

``[exit]`` - Exits the shell. <br  />

``[pwd]`` - Prints the current working directory. <br  />

``[quit]`` - An alias for the exit command, exits the shell. <br  />   <br  />

  

Additionally, the shell can execute any external command available on the system using the execve() function. For example, on Linux, the shell can run commands like ls, and on Windows, it can run dir, provided these commands are available as executables on the system.

  

## How to Check if a Command is Built-in or External

Some commands are considered built-in to this shell, while the system you are running the shell on may recognize them as external commands. To check whether a command is built-in or external on your system, you can use the which command: <br  />

```sh

which [command]

```

If which returns a path (e.g., /bin/ls), the command is recognized as an external binary executable program.

If which does not return a path and instead gives an error, the command is either a built-in shell command or an invalid command. <br  />

For example:<br  />



```sh

which  ls

```

Output: <br  />

```bash

/bin/ls

```

This means ls is an external command located in [/bin/ls]. <br  /><br  />

  

Alternatively: <br  />

  

```sh

which [echo]

```

Output (in most cases): <br  />

  

```bash

echo:  shell  built-in  command

```

This means echo is a built-in command in most shells. <br  />

  

## Usage

To use this shell, simply run the program, and you will enter a custom shell prompt. You can then type any of the built-in (internal) commands or external system commands. <br  />

  

### Examples

echo: ```echo "Hello World!"``` or <br  />
> The echo command simply outputs the provided string to stdout. For example, ``echo hello`` will print ``hello`` to stdout. ``echo "This is a message"`` will output ``This is a message``.  When using the echo command, use quotations if the provided string is longer than one word. <br  />

cd: ```cd /path/to/directory```<br  />
> The cd command simply changes the current working directory. When using the cd command, use quotations if the provided directory contains any spaces. <br  />

setenv: ```setenv VAR=value```<br  />
> The setenv command adds a variable and its value to the environment variables. **setenv only modifies environment variables for the duration of this program's process. Should the program terminate, the environment variables will be reverted to the default system environment variables** When using the setenv command, the variable and its value should be all in one word, separated by ``=`` instead of a space. For example, ``setenv MY_VARIABLE=value``. <br  />

unsetenv: ```unsetenv VAR```<br  />
> The unsetenv command removes a variable and its value from the environment variables.  When using unsetenv only provide the variable name when running the command. For example, ``unsetenv MY_VARIABLE``. <br  />

env: ```env```<br  />
> The env command prints all environment variables on the current process. <br  />

pwd: ```pwd```<br  />
> The pwd command prints the path of the current working directory. <br  />

exit or quit: ```exit``` or ```quit```  <br  />
> The exit or quit commands terminate the current process. <br  />

Depending on your operating system, you can also run external system commands like ``ls``, ``dir``, ``cat``, ``tail``, ``head`` etc. <br  />

  

## Exit

To exit the program, you can use the exit or quit commands. <br  />

  

> [!NOTE] 
> The execve() function is used for external commands. The program is able to run any valid executables available on the system.
The shell only supports basic functionality for the built-in commands and does not handle advanced shell scripting or piping.

<br  />

> [!IMPORTANT]
Given the right path, this program cannot only execute external commands, it can execute any binary executable file. The provided ``[test_segfault_command.exe]`` file provided in this repository, is provided to verify that the program can run and check for segfaults in an executed program. To test this feature, execute``[test_segfault_command.exe]``.  <br  />

  

##### Executing another executable program (commands to input in my_shell.exe);

```sh

$>./test_segfaulting.exe

```

##### Output: <br  />

  

```

Segfault

```

### Prerequisites

- GCC (GNU Compiler Collection) or any other C compiler. <br  />

- GNU make. <br  />

  

### Compilation and Execute

##### To compile the program, use the following command: <br  />

```sh

make

```

  

##### To execute the program, use the following command: <br  />

```sh

./my_shell.exe

```

  

##### Acknowledgments

created by Paul Mwaura  

<span><i>This README file provides clear instructions on how to compile, and run the program, as well as examples of usage options. It also highlights disclaimers on the limits of the program compared to bash. </a></i></span>