#include "../headers/parse_input.h"

char* my_strtok(char *str, const char *delimiters) {
    static char *nextToken = NULL;  // Stores the remaining string for the next call
    char *start;                    // Points to the start of the current token
    bool foundDelimiter;            // Flag to check if a delimiter is found

    // If str is not NULL, this is the first call for a new string
    if (str != NULL) {
        nextToken = str;
    }

    // If nextToken is NULL, return NULL as there are no more tokens
    if (nextToken == NULL) {
        return NULL;
    }

    // Skip leading delimiters
    start = nextToken;
    foundDelimiter = false;
    while (*start != '\0') {
        for (int i = 0; delimiters[i] != '\0'; i++) {
            if (*start == delimiters[i]) {
                start++;
                foundDelimiter = true;
                break;
            }
        }
        if (!foundDelimiter) break;
        foundDelimiter = false;
    }

    // If we've reached the end of the string, return NULL
    if (*start == '\0') {
        nextToken = NULL;
        return NULL;
    }
    // Find the end of the token
    nextToken = start;
    while (*nextToken != '\0') {
        for (int i = 0; delimiters[i] != '\0'; i++) {
            if (*nextToken == delimiters[i]) {
                *nextToken = '\0';  // Replace the delimiter with a null terminator
                nextToken++;        // Move to the next character for future calls
                return start;
            }
        }
        nextToken++;
    }

    // If we reached the end without finding another delimiter
    nextToken = NULL;
    return start;
}

bool has_explicit_string(char* input)
{
    bool open_quote = false;
    bool close_quote = false;

    for(int i = 0; i < (int)strlen(input); i++)
    {
        if(input[i] == '\"' && open_quote == false)
            open_quote = true;
        if(input[i] == '\"' && open_quote == true)
            close_quote = true;
    }
    if(open_quote && close_quote)
    {
        return true;
    }
    return false;
}

char** tokenize_string(char *input)
{
    // Need to implement a way to dynamically allocate result
    char **result = malloc(50 * sizeof(char));
    char delimiter[8];
    char* token;

    // we need to check if there are any quoted strings first.
    //  - If their is, we will set delimiter to "\"", and tokenize on that.
    //  - If not, we will token reguraly with " ".
    if(has_explicit_string(input))
    {
        strcat(delimiter, "\"");
    }
    else
    {
        strcat(delimiter, " ");
    }
    token = my_strtok(input, delimiter);
    int k = 0;
    while( token != NULL)
    {
        result[k] = token;
        k++;
        token = my_strtok(NULL, delimiter);
    }
    result[k] = NULL;
    // delimiter = NULL;
    return result;
}

// int main()
// {
//     char str[] = "This is a test \"hello world\" test test test";
//     char str[] = "This is a test hello world test test test";

//     tokenize_string(str);
//     return 0;
// }