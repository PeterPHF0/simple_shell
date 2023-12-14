/**
 * cce - command exists in one of the directories in path.
 * @command: a command to be checked.
 *
 * Return: 1 command exists.
 */
int cce(char *command)
{
char *path;
char *path_copy;
char *dir;
if (command[0] == '/')
{
if (access(command, X_OK) == 0)
return (1);
else
return (0);
}
path = getenv("PATH");
if (path == NULL)
{
write(STDERR_FILENO, "Error: PATH environment variable not set.\n", 41);
exit(EXIT_FAILURE);
}
path_copy = strdup(path);
if (path_copy == NULL)
{
perror("Error duplicating PATH");
exit(EXIT_FAILURE);
}
dir = strtok(path_copy, ":");
while (dir != NULL)
{
char full_path[MAX_COMMAND_LENGTH];
snprintf(full_path, sizeof(full_path), "%s/%s", dir, command);
if (access(full_path, X_OK) == 0)
{
free(path_copy);
return (1);
}
dir = strtok(NULL, ":");
}
free(path_copy);
return (0);
}

