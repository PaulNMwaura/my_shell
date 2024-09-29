#include "../headers/main.h"
#include "../headers/builtin.h"
#include "../headers/handle_args.h"

void echo(char *argument)
{
    // if(execute[0] == '$') {
    //     char* name = extract_name(execute);
    //     echo_value(name, env);
    // }

    // using write() as a requirement, but we can switch back to simple printf.
    for (int i = 0; i < (int)strlen(argument); i++)
    {
        if (argument[i] != '"')
        {
            write(2, &argument[i], 1);
        }
    }
    write(2, "\n", 1);
}

void cd(char *argument)
{
    if (argument != NULL)
    {
        if ((strcmp(argument, "-") == 0))
        {
            /* Need to check that argument is actually == "-" and not "- " or " -"*/
            char cwd[100]; /* current working directory. */
            char pwd[100]; /* present working directory. */
            if (getcwd(cwd, sizeof(cwd)) != NULL)
            {
                chdir("../");
                getcwd(pwd, sizeof(pwd));
                printf("present dir: %s\n", pwd);
            }
        }
        else
        {
            chdir(argument);

            /*    below is debugging code to confirm that cd is working    */
            // char cwd[1024];
            // if (getcwd(cwd, sizeof(cwd)) != NULL)
            //     printf("Current working directory: %s\n", cwd);
        }
    }
}

void my_exit()
{
    exit(EXIT_SUCCESS);
}

void pwd()
{
    char pwd[100];
    if (getcwd(pwd, sizeof(pwd)) != NULL)
    {
        printf("%s\n", pwd);
    }
}

void print_variables(char **env)
{
    while(*env !=  NULL)
    {
        printf("%s\n", *env);
        env++;
    }
}

void which(char *argument)
{
    int command_ID = is_builtin_command(argument);
    if (command_ID != -1)
    {
        printf("%s: shell built-in command\n", argument);
    }
    else
    {
        printf("finding %s directory\n", argument);
        // create path string;
        // find directory and concat the dir path to path string
        // print path string;
        // free path;

        char *path = malloc(sizeof(char) * (10 + strlen(argument)));
        strcat(path, "/usr/bin/");
        strcat(path, argument);
        printf("%s\n", path);
        if (strcmp(path, "/usr/bin/") == 0)
        {
            printf("%s: command not found\n", argument);
        }
        free(path);
    }
}

int my_setenv(char** env, char *execute, int overwrite) {
    char** variable = (char**)malloc(strlen(execute) * sizeof(char*));
    char* token = strtok(execute, "=");
    int k = 0;
    while( token != NULL)
    {
        variable[k] = token;
        k++;
        token = strtok(NULL, "=");
    }
    variable[k] = NULL;
    char* name = variable[0];
    char* value = variable[1];
    free(variable);

    if (name == NULL || value == NULL || strchr(name, '=') != NULL) {
        // Invalid arguments: name cannot be NULL, value cannot be NULL, name cannot contain '='
        return -1;
    }

    // Check if the environment variable already exists
    size_t name_len = strlen(name);
    for (int i = 0; env[i] != NULL; i++) {
        // Look for an existing entry of "NAME=value"
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=') {
            // Variable found
            if (overwrite == 0) {
                // Don't overwrite if overwrite is 0
                return 0;
            } else {
                // Overwrite the existing environment variable
                size_t new_var_len = name_len + strlen(value) + 2; // +2 for '=' and null terminator
                char *new_var = (char *)malloc(new_var_len);
                if (new_var == NULL) {
                    // Memory allocation failure
                    return -1;
                }
                snprintf(new_var, new_var_len, "%s=%s", name, value);
                env[i] = new_var;
                return 0;
            }
        }
    }

    // If the variable doesn't exist, add a new environment variable
    size_t new_var_len = name_len + strlen(value) + 2; // +2 for '=' and null terminator
    char *new_var = (char *)malloc(new_var_len);
    if (new_var == NULL) {
        // Memory allocation failure
        return -1;
    }
    snprintf(new_var, new_var_len, "%s=%s", name, value);

    // Count the current number of environment variables
    int env_count = 0;
    while (env[env_count] != NULL) {
        env_count++;
    }

    // Reallocate the environment array to hold the new variable
    char** new_env = (char**)malloc((env_count + 2) * sizeof(char*));
    if (new_env == NULL) {
        free(new_var); // Clean up on failure
        return -1;
    }

    for(int i = 0; i < env_count; i++)
        new_env[i] = env[i];

    env = new_env;
    env[env_count] = new_var;      // Add the new variable
    env[env_count + 1] = NULL;     // Terminate with a NULL pointer

    for(int i = 0; i < env_count + 2; i++)
        environ[i] = env[i];
    free(env);
    return 0;
}

// Custom unsetenv function
int my_unsetenv(char** env, const char* name) {
    if (name == NULL || strchr(name, '=') != NULL) {
        // Invalid name: can't be NULL and can't contain '='
        return -1;
    }

    size_t name_len = strlen(name);
    int env_count = 0;

    // Find the environment variable and its position
    for (int i = 0; env[i] != NULL; i++) {
        env_count++;
        if (strncmp(env[i], name, name_len) == 0 && env[i][name_len] == '=') {
            // Variable found: free the memory for this entry
            free(env[i]);

            // Shift all remaining variables down by one position
            for (int j = i; env[j + 1] != NULL; j++) {
                env[j] = env[j + 1];
            }

            // Null-terminate the array one element earlier
            env[env_count - 1] = NULL;
            
            for(int i = 0; i < env_count; i++)
                environ[i] = env[i];
            return 0;
        }
    }

    free(env);
    // Variable not found
    return 0;
}

void execute_builtin(int command_ID, char *argument, char **env)
{
    switch (command_ID)
    {
    case 0:
        echo(argument);
        break;
    case 1:
        cd(argument);
        break;
    case 2:
        my_setenv(env, argument, 1);
        break;
    case 3:
        my_unsetenv(env, argument);
        break;
    case 4:
        print_variables(environ);
        break;
    case 5:
        my_exit();
        break;
    case 6:
        pwd();
        break;
    case 7:
        my_exit();
        break;
    default:
        break;
    }
}