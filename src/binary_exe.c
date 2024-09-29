#include "../headers/binary_exe.h"

char *extract_filename(char *argument)
{
    char *command = (char *)malloc(strlen(argument) - 1);
    int k = 0;
    for (int i = 2; i < (int)strlen(argument); i++)
    {
        command[k] = argument[i];
        k++;
    }
    command[k] = '\0';
    return command;
}

void execute_file(char** args, char** env)
{
    char* filename = extract_filename(args[0]);
    char* path = malloc(100);
    path = getcwd(path, 100);
    strcat(path, "/");
    strcat(path, filename);
    if(path != NULL)
    {
        executor(path, args, env);
    }
    free(path);
}

int executor(char* path, char** args, char** env) 
{
    pid_t pid;
    int status;
    int exit_status = 0;
    pid = fork();
    if (pid == 0) 
    {
        if (execve(path, args, env) == -1) 
        {
            exit_status++;
            return exit_status;
        }
    } 
    else 
    {
        do 
        {
            waitpid(pid, &status, WUNTRACED);
            if (WIFEXITED(status))
            {
                exit_status = WEXITSTATUS(status);
            } 
            else if (WIFSIGNALED(status)) 
            {
                int signal = WTERMSIG(status);
                if (signal == SIGSEGV) 
                {
                    write(2, "segmentation fault\n", 20);
                }
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return exit_status;
}