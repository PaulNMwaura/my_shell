#include "../headers/read_input.h"


char* read_line(int fd) 
{
    int MAX_SIZE = 1024, i = 0, bytes_read;
    char* buf = malloc(MAX_SIZE + 1 * sizeof(char));
    char c;

    while(i < MAX_SIZE - 1 && (bytes_read = read(fd, &c, sizeof(char)) > 0)) 
    {
        if(c == '\0' || c == '\n') 
        {
            break;
        }
        else 
        {
            buf[i] = c;
            i++;
        }
    }
    if(bytes_read <= 0) 
    {
        free(buf);
        return 0;
    }
    buf[i] = '\0';
    return buf;
}

char* read_input() 
{
    char* input = NULL;
    int READLINE_READ_SIZE = 1024, count = 0;
    int fd = 0;

    if (fd == -1) 
    {
        printf("Error: Could not read input.\n");
        return NULL;
    }
    // Read command from STDIN
    while (count < READLINE_READ_SIZE && (input = read_line(fd)) != 0) 
    {
        // printf("*** %s ***\n", input);
        if(input == NULL)
        {
            printf("Invalid input\n");
        }
        else
        {
            return input;
        }
    }
    close(fd);
    fflush(stdout);    
    return NULL;
}