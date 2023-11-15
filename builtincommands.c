#include "main.h"
/**
 * changedirectory - function changes the current working
 * directory to the specified path.
 * @pathdir: Path to the current working directory.
 *
 * Description: function changes the current working
 * directory to the specified path.
 */
void changedirectory(char *pathdir)
{
	if (pathdir == NULL)
		chdir(getenv("HOME"));
	else if (strcmp(pathdir, "-") == 0)
	{
		char *oldpwd = getenv("OLDPWD");

		if (oldpwd != NULL)
		{
			printf("%s\n", oldpwd);
			chdir(oldpwd);
			setenv("OLDPWD", getcwd(NULL, 0), 1);
		}
		else
			fprintf(stderr, "OLDPWD not set\n");
	}
	else
	{
		char *currentDir = getcwd(NULL, 0);

		chdir(pathdir);
		setenv("OLDPWD", currentDir, 1);
		free(currentDir);
	}
}
/**
 * myexit - This function exits the shell.
 * @exitargument: Pointer the exit argument provided.
 *
 * Description: Function exits the shell.
 */
void myexit(char *exitargument)
{
	if (exitargument != NULL)
		exit(atoi(exitargument));
	else
		exit(0);
}

/**
 * envir - This function prints all the environment variables.
 *
 * Description: - This function prints all the environment variables.
 * Return:  1 if successful.
 */
int envir(void)
{
	char **env = environ;

	while (*env != NULL)
	{
		printf("%s\n", *env);
		env++;
	}
	return (1);
}
