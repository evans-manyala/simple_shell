#include "main.h"

/**
 * main - This is the main function for our shell program.
 * Return: Returns nothing(void)
 * Description: This is the main function for our shell program.
 */

int main(void)
{
	static char buffer[100];

	while (get_func(buffer, sizeof(buffer)) >= 0)
	{
		if (buffer[0] == 'c' && buffer[1] == 'd')
		{
			char *path = NULL;

			if (strlen(buffer) > 2)
				path = buffer + 3;
			changedirectory(path);
		}
		else if (buffer[0] == 'e' && buffer[1] == 'x'
		&& buffer[2] == 'i' && buffer[3] == 't')
		{
			char *exargs = NULL;

			if (strlen(buffer) > 4)
				exargs = buffer + 5;
			myexit(exargs);
		}
		else if (buffer[0] == 'e' && buffer[1] == 'n' && buffer[2] == 'v')
			envir();
		else if (fork_func() == 0)
			run_func(parse_func(buffer));
		wait(0);
	}
	exit(0);
}

/* Helper functions */

/**
 * panicerror - Prints out an error message and terminate the process
 * @s: The error to print out
 * Return: Returns nothing(void)
 */
void panicerror(char *s)
{
	printf("%s\n", s);
	exit(1);
}

/**
 * fork_func - Wrapper for the fork system call
 * Return: process id
 *
 * Description: Wrapper for the fork system call
 */
int fork_func(void)
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		panicerror("fork");
	}
	return (pid);
}

/**
 * get_func - Prints the shell prompt and used in the main control loop
 * @buffer: The buffer character array cintaining the input
 * @nbuffer: Number of characters in the buffer array
 * Return: Returns 0 on Success
 */

int get_func(char *buffer, int nbuffer)
{
	size_t len;
	
	printf("$ ");
	memset(buffer, 0, nbuffer);

	fgets(buffer, nbuffer, stdin);

	len = strlen(buffer);

	if (len > 0 && buffer[len - 1] == '\n')
		buffer[len - 1] = '\0';
	if (buffer[0] == '#')
		buffer[0] = '\0';
	if (buffer[0] == 0)
		return (-1);
	return (0);
}
