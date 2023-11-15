#include "main.h"
/**
 * nulterminate - structure for null-terminstion of strings
 * @func: Pointer to the function to be executed.
 * Return: Pointer to the function to be executed.
 *
 * Description:  function is designed to null-terminate
 * strings within a given data structure represented
 * by the struct func and its derived structures.
 */
struct func *nulterminate(struct func *func)
{
	int x;
	struct backfunc *bfunc;
	struct execfunc *efunc;
	struct listfunc *lfunc;

	if (func == 0)
		return (0);
	switch (func->type)
	{
	case EXEC:
		efunc = (struct execfunc *)func;

		for (x = 0; efunc->argv[x]; x++)
			*efunc->eargv[x] = 0;
		break;

	case LIST:
		lfunc = (struct listfunc *)func;
		nulterminate(lfunc->left);
		nulterminate(lfunc->right);
		break;

	case BACK:
		bfunc = (struct backfunc *)func;
		nulterminate(bfunc->func);
		break;
	}
	return (func);
}
