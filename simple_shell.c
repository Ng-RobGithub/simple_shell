#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_INPUT_LEN 1024

int main(void)
{
	char input[MAX_INPUT_LEN];
	char *args[2];
	pid_t pid;
	int status;

	while (1)
	{
		printf("#cisfun$ ");

		if (!fgets(input, MAX_INPUT_LEN, stdin))
		{
			printf("\n");
			break; /* End of file (Ctrl+D) */
		}

		/* Remove trailing newline */
		input[strcspn(input, "\n")] = 0;

		/* Tokenize input */
		args[0] = input;
		args[1] = NULL;

		/* Fork a child process */
		pid = fork();

		if (pid < 0)
		{
			perror("Fork failed");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{ /* Child process */
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Execve failed");
				exit(EXIT_FAILURE);
			}
		} else
		{ /* Parent process */
			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
