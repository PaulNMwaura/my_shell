#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>


char* read_line(int fd);
char* read_input();