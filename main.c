#include "shell.h"

/**
 * main - Entry point of the simple shell program
 * @argc: Number of arguments passed to the program
 * @argv: Array of pointers to the arguments passed to the program
 *
 * Return: Always returns 0 on success
 */
int main(int argc, char **argv)
{
	int fd = STDERR_FILENO;
	info_t info = {0}; /* Initialize info structure */

/* Adjusting file descriptor using inline assembly */
	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

/* Check if a file name is provided as argument */
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd == -1)
		{
/* Handle error opening file */
			handle_open_error(argv[0], argv[1]);
			return (EXIT_FAILURE);
		}
		info.readfd = fd; /* Update read file descriptor in info structure */
	}

/* Populate environment list and read command history */
	populate_env_list(&info);
	read_history(&info);

/* Start the shell with the provided info */
	hsh(&info, argv);

/* Clean up and exit */
	close(fd);
	return (EXIT_SUCCESS);
}
