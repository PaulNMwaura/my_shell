#include "../headers/main.h"
#include "../headers/read_input.h"
#include "../headers/parse_input.h"
#include "../headers/handle_args.h"

void execute(char* input, char** env)
{
    if (input[0] == '\0')
        input = NULL;
    if (input != NULL)
    {
        //____________________________________________________________________________________
        // parse input: Tokenize it and store the input into an array
        // keep in mind that the array could be structured differently depending on the input
        //      - echo "This is a message" vs echo message
        //      - cd "file 1" vs cd file1
        char **args = tokenize_string(input);
        //____________________________________________________________________________________

        //____________________________________________________________________________________
        // Handle args by checking what type of commands were in the input.
        // For example if the arugment is a builtin command, or a binary executable.
        handle_args(args, env);
        //____________________________________________________________________________________

        free(input);
        free(args);
    }
}

int main(int argc, char **argv)
{
    char **env = environ;
    if (argc == 1 && argv != NULL)
    {
        // read user input and store it in a string.
        char *input = read_input();
        while (input)
        {
            execute(input, env);
            input = read_input();
        }
    }
     // setting variables to updated environment;
    return 0;
}