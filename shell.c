#include "shell.h"

#define _POSIX_C_SOURCE 200809L

/**
 * main - Entry point of the simple shell program
 *
 * Return: Always returns 0 on success
 */
int main(void)
{
	char *input_buffer = NULL; /* Declare input_buffer as a pointer to char */
	size_t buffer_size = 0; /* Initialize buffer_size to 0 */
	ssize_t characters_read;
	pid_t pid;
	int status;

	while (1)
	{
/* Display prompt*/
		printf("%s", PROMPT);
		characters_read = _getline(&input_buffer, &buffer_size,
				           &input_buffer_size, stdin); 
		         /* Pass the address of input_buffer and buffer_size */
		if (characters_read == -1) /* Handle EOF or error */
        {
            if (isatty(STDIN_FILENO))
                printf("\n");
            free(input_buffer);
            exit(EXIT_SUCCESS);
        }

/* Read input from user */
		int _getline(info_t *info, char **line, size_t *len);
		if (characters_read == -1) /* Handle EOF */
		{
			putchar('\n'); /* Print newline before exiting */
			free(input_buffer);
			exit(EXIT_SUCCESS);
		}

/* Remove newline character */
		input_buffer[strcspn(input_buffer, "\n")] = '\0';

/* Fork a child process */
		pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(input_buffer);
			exit(EXIT_FAILURE);
		}
		if (pid == 0) /* Child process */
		{
			/* Execute the command */
			if (execlp(input_buffer, input_buffer, NULL) == -1)
			{
/* Print error message if command not found */
				perror(input_buffer);
				exit(EXIT_FAILURE);
			}
		}
		else /* Parent process */
		{
			/* Wait for the child process to finish */
			if (wait(&status) == -1)
			{
				perror("wait");
				free(input_buffer);
				exit(EXIT_FAILURE);
			}
		}
	}

/* Free allocated memory and exit */
	free(input_buffer);
	return (EXIT_SUCCESS);
}
