#include "../headers/handle_args.h"
#include "../headers/builtin.h"
#include "../headers/binary_exe.h"

char *trim_leading_space(char *string)
{
    for (int i = 0; i < (int)strlen(string); i++)
    {
        if (string[i] == ' ' && i > 0)
        {
            string[i] = '\0';
            break;
        }
    }
    return string;
}

// This function returns a corresponding index number, if args contains a builtin command.
int is_builtin_command(char* argument)
{
    char* builtin[] = {"echo","cd","setenv","unsetenv","env","exit","pwd", "quit", NULL};
    for(int i = 0; i < 8; i++)
    {
        if(strcmp(argument, builtin[i]) == 0)
            return i;
    }
    return -1;
}

bool is_exe(char **args)
{
    if (args[0][0] == '.' && args[0][1] == '/')
        return true;
    return false;
}

void handle_args(char **args, char **env)
{
    char *command = trim_leading_space(args[0]);
    int command_ID = is_builtin_command(command);
    if (command_ID != -1)
    {
        // We are working with a builtin command here.
        execute_builtin(command_ID, args[1], env);
    }
    else
    {
        /*
            We need to first check if the command is trying to execute a program
            ex: ./a.out
        */
        if (is_exe(args))
        {
            execute_file(args, env); 
        }
        else
        {
            // We are working with binary executable command here.
            char* path = malloc(sizeof(char) * (11 + strlen(command)));
            strcpy(path, "/usr/bin/");
            strcat(path, command);
            if(executor(path, args, env) > 0)
                printf("command not found\n");
            // path = NULL; //free(path) doesn't seem to work as intended, so path is being hard reset to NULL.
            free(path);
        }
    }
}