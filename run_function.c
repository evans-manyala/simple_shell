#include "main.h"

/**
 * exec_cmd - a command using the execve system call
 * @full_path: The full path of the command to execute
 * @argv: The command-line arguments
 */
void exec_cmd(char *full_path, char **argv)
{
	if (execve(full_path, argv, NULL) < 0)
	{
		perror("execve");
		exit(1);
	}
}

/**
 * forkNwait - Fork a child process and wait for it to finish
 * @func: The function to execute in the child process
 */
void forkNwait(struct func *func)
{
	if (fork_func() == 0)
		run_func(func);
	else
		wait(0);
}
/**
 * searchNexecute_cmd - Search for and execute a command in the PATH
 * @command_name: The command to search for
 * @argv: The arguments for the command
 *
 * Description: This function searches for the specified command in the PATH
 * and executes it if found. If the command is not found, it prints an error
 * message and exits with an error code.
 */

void searchNexecute_cmd(char *command_name, char **argv)
{
	char *path_env = getenv("PATH");
	char *path = strdup(path_env);
	char *dir = strtok(path, ":");

	while (dir != NULL)
	{
		char full_path[1024];

		snprintf(full_path, sizeof(full_path), "%s/%s", dir, command_name);

		if (access(full_path, X_OK) == 0)
		{
			exec_cmd(full_path, argv);
		}

		dir = strtok(NULL, ":");
	}

	printf("Command not found: %s\n", command_name);
	exit(1);
}

/**
 * run_func - Final execution of the shell program
 * @func: The function to execute
 * Return : Does not return anything (void)
 */
void run_func(struct func *func)
{
	switch (func->type)
	{
	case EXEC:
	{
		struct execfunc *efunc = (struct execfunc *)func;

		if (efunc->argv[0] == 0)
			exit(1);
		if (strchr(efunc->argv[0], '/'))
			exec_cmd(efunc->argv[0], efunc->argv);
		else
			searchNexecute_cmd(efunc->argv[0], efunc->argv);
		break;
	}
	case LIST:
	{
		struct listfunc *lfunc = (struct listfunc *)func;

		forkNwait(lfunc->left);
		forkNwait(lfunc->right);
		break;
	}
	case BACK:
	{
		struct backfunc *bfunc = (struct backfunc *)func;

		forkNwait(bfunc->func);
		break;
	}
	default:
		panicerror("run_func");
	}
	exit(0);
}
