#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char *extract_filename(char *argument);
void execute_file(char** args, char** env);
int executor(char* path, char** args, char** env);
void execute_file(char** args, char** env);
