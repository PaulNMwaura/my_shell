#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

char* my_strtok(char *str, const char *delimiters);
bool has_explicit_string(char* input);
char** tokenize_string(char *input);
