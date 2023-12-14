#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

#define MAX_COMMAND_LENGTH 1024
#define MAX_ARGUMENTS 10
/**
 * pe - current environment variables.
 */
void pe(void)
{
    char **env;

    for (env = environ; *env != NULL; env++)
    {
        write(STDOUT_FILENO, *env, strlen(*env));
        write(STDOUT_FILENO, "\n", 1);
    }
}
