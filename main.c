#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * main - Entry point of the program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
int status;
char *input = NULL;
size_t input_size = 0;
while (printf("$ "), getline(&input, &input_size, stdin) != -1)
{
size_t length = strlen(input);
if (input[length - 1] == '\n')
input[length - 1] = '\0';
char *token, *args[MAX_ARGUMENTS];
int arg_count = 0;
for (token = strtok(input, " "); token && arg_count < MAX_ARGUMENTS;
token = strtok(NULL, " "))
args[arg_count++] = token;
args[arg_count] = NULL;
if (strcmp(args[0], "exit") == 0)
{
printf("Exiting the shell.\n");
free(input);
exit(EXIT_SUCCESS);
}
else if (!cce(args[0]))
{
fprintf(stderr, "Command not found: %s\n", args[0]);
continue;
}
pid_t pid = fork();
if {
	(pid < 0) perror("Fork failed"), exit(EXIT_FAILURE);
}
else if
{
	(pid == 0) execvp(args[0], args)
	perror("Error executing command"
	exit(EXIT_FAILURE);
}
else
waitpid(pid, &status, 0);
}
free(input);
return (0);
}
