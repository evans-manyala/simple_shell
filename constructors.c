#include "main.h"

/**
 * execfunc - Allocates and initializes an execfunc struct
 * Return: A pointer to the newly allocated execfunc struct
 */
struct func *execfunc(void)
{
	struct execfunc *func;

	func = malloc(sizeof(struct execfunc));
	if (!func)
		panicerror("malloc failed");
	memset(func, 0, sizeof(struct execfunc));
	func->type = EXEC;
	return ((struct func *)func);
}

/**
 * listfunc - Allocates and initializes a listfunc struct
 * @left: The left subfunction
 * @right: The right subfunction
 * Return: A pointer to the newly allocated listfunc struct
 */
struct func *listfunc(struct func *left, struct func *right)
{
	struct listfunc *func;

	func = malloc(sizeof(struct listfunc));
	if (!func)
		panicerror("malloc failed");
	memset(func, 0, sizeof(struct listfunc));
	func->type = LIST;
	func->left = left;
	func->right = right;
	return ((struct func *)func);
}

/**
 * backfunc - Allocates and initializes a backfunc struct.
 * @subfunc: The subfunction to run in the background
 * Return: A pointer to the newly allocated backfunc struct
 */
struct func *backfunc(struct func *subfunc)
{
	struct backfunc *func;

	func = malloc(sizeof(struct backfunc));
	if (!func)
		panicerror("malloc failed");
	memset(func, 0, sizeof(struct backfunc));
	func->type = BACK;
	func->func = subfunc;
	return ((struct func *)func);
}

/**
 * parse_func - Parses a shell command & constructs a corresponding func struct
 * @s: The input string containing the shell command
 * @es: The end of the input string
 * Return: A pointer to the parsed func struct
 */
struct func *parse_func(char *s, char *es)
{
	struct func *func;

	func = parseline(&s, es);
	if (s != es)
	{
		printf("Invalid command: %s\n", s);
		panicerror("syntax");
	}
	nulterminate(func);
	return (func);
}
