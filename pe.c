#include "main.h"
/**
 * pe - current environment variables.
 */
void pe(void)
{
char **environ;
char **env;

for (env = environ; *env != NULL; env++)
{
write(STDOUT_FILENO, *env, strlen(*env));
write(STDOUT_FILENO, "\n", 1);
}
}
