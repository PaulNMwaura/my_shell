#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int is_builtin_command(char* argument);
void handle_args(char** args, char** env);