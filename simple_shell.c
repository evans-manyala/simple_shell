#include "main.h"

/**
 * read_cmd - Function reads a command line from the user
 * Return: Line
 * */
char *read_cmd()
{
	char *line = NULL;
	size_t len = 0;

	printf(PROMPT);
	getline(&line, &len, stdin);

	/* Remove the newline character at the end of the line */
	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';
	return (line);
}

/**
 * execute_cmd - Function executes a command.
 * @cmd: Pointer for the commmand to be executed.
 * Return: If successful 0, otherwise -1
 */

int execute_cmd(char *cmd)
{
	/*Create a child process*/
	pid_t child_pid = fork();

	if (child_pid < 0)
	{
		/*Error forking*/
		perror("fork");
		return (-1);
	}
	else if (child_pid == 0)
	{
		/*Child process*/
		/*Execute the command*/
		execve(cmd, NULL, environ);
		/*If we reach here, something went wrong*/
		perror("execve");
		exit(1);
	}
	else
	{
		/*Parent process*/
		/* Wait for the child process to finish executing */
		int status;

		waitpid(child_pid, &status, 0);

		/* Check the exit status of the child process */
		if (status != 0)
		{
			/* Error executing the command */
			printf("Error executing command: %s\n", cmd);
			return (-1);
		}
	}
	return (0);
}

/**
 * handle_eof - Checks for and handles  the end of file condition
 */

void handle_eof(void)
{
	printf("\n");
	exit(0);
}

/**
 * main - Main function in the shell script
 * Return: 0 if successful.
 */
int main(void)
{
	/* Handle the end of file condition */
	signal(SIGINT, handle_eof);

	/* Infinite loop */
	while (1)
	{
		/* Read a command line from the user */
		char *cmd = read_cmd();

		/* If the command is empty, skip it */
		if (strlen(cmd) == 0)
		{
			continue;
		}

		/* Execute the command */
		execute_cmd(cmd);

		/* Free the command line */
		free(cmd);
	}
	return (0);
}
