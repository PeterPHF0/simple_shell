#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_INPUT_SIZE 1024
#define MAX_ARG_SIZE 64

void execute_command(char **args) {
    pid_t pid, wpid;
    int status;

    pid = fork();
    if (pid == 0) {
        // Child process
        if (strchr(args[0], '/') == NULL) {
            // If the command does not contain a path separator (/), try to find it in PATH
            char *path = getenv("PATH");
            if (path != NULL) {
                char *token = strtok(path, ":");
                while (token != NULL) {
                    char full_path[MAX_INPUT_SIZE];
                    snprintf(full_path, sizeof(full_path), "%s/%s", token, args[0]);

                    if (access(full_path, X_OK) == 0) {
                        execve(full_path, args, NULL);
                        // If execve fails, continue searching in PATH
                    }

                    token = strtok(NULL, ":");
                }
            }

            // If not found in PATH, print an error
            perror("shell");
            _exit(EXIT_FAILURE);
        } else {
            // If the command contains a path separator, execute it directly
            execve(args[0], args, NULL);
            perror("shell");
            _exit(EXIT_FAILURE);
        }
    } else if (pid < 0) {
        perror("shell");
    } else {
        // Parent process
        do {
            wpid = waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

int parse_input(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " \t\n\r\a");

    while (token != NULL && i < MAX_ARG_SIZE - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n\r\a");
    }
    args[i] = NULL;

    return i;
}

int main() {
    char input[MAX_INPUT_SIZE];
    char *args[MAX_ARG_SIZE];

    while (1) {
        printf("shell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            perror("shell");
            exit(EXIT_FAILURE);
        }

        // Remove newline character
        size_t input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        int arg_count = parse_input(input, args);

        if (arg_count > 0) {
            if (strcmp(args[0], "exit") == 0) {
                // Exit the shell
                exit(EXIT_SUCCESS);
            } else {
                execute_command(args);
            }
        }
    }

    return 0;
}
