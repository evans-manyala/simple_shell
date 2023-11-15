#include "main.h"

struct func *parseline(char **ps, char *es);
struct func *parseexec(char **ps, char *es);
struct func *parseblock(char **ps, char *es);

static const char whitespace[] = " \t\r\n\v";
static const char symbols[] = "<|>&;()";

/**
 * gettoken - Retrieves the next token from the input string.
 * @ps: Pointer to the pointer input string.
 * @es: Pointer to the End string.
 * @q: Pointer to the beginning of the string.
 * @eq: Pointer to the end of the string.
 * Return: Retrieved token
 *
 * Description: Retrieves the next token from the input string.
*/
int gettoken(char **ps, char *es, char **q, char **eq)
{
	char *s;
	int ret;

	s = *ps;

	while (s < es && strchr(whitespace, *s))
		s++;
		if (q)
			*q = s;
	ret = *s;
	switch (*s)
	{
	case 0:
		break;
	case '|':
	case '(':
	case ')':
	case ';':
	case '&':
	case '<':
		s++;
		break;
	case '>':
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
		break;
	default:
		ret = 'a';
		while (s < es && !is_whitespace_or_symbol(*s))
			s++;
		break;
	}
	if (eq)
		*eq = s;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return (ret);
}
int peek(char **ps, char *es, char *toks)
{
	char *s;

	s = *ps;
	while (s < es && strchr(whitespace, *s))
		s++;
	*ps = s;
	return (*s && strchr(toks, *s));
}

struct func *parseline(char **ps, char *es)
{
	struct func *func;

	func = parseexec(ps, es);
	while (peek(ps, es, "&"))
	{
		gettoken(ps, es, 0, 0);
		func = backfunc(func);
	}
	if (peek(ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		func = listfunc(func, parseline(ps, es));
	}
	return (func);
}

struct func *parseblock(char **ps, char *es)
{
	struct func *func;

	if (!peek(ps, es, "("))
		panicerror("parseblock");
	gettoken(ps, es, 0, 0);
	func = parseline(ps, es);
	if (!peek(ps, es, ")"))
		panicerror("syntax - missing )");
	gettoken(ps, es, 0, 0);
	return (func);
}

struct func *parseexec(char **ps, char *es)
{
	char *q, *eq;
	int tok, argc;

	struct execfunc *func;
	struct func *ret;

	if (peek(ps, es, "("))
		return (parseblock(ps, es));
	ret = execfunc();
	func = (struct execfunc *)ret;
	argc = 0;

	while (!peek(ps, es, "|)&;"))
	{
		tok = gettoken(ps, es, &q, &eq);
		if (tok == 0)
			break;
		if (tok != 'a')
			panicerror("syntax");
		func->argv[argc] = q;
		func->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
			panicerror("too many args");
	}
	func->argv[argc] = 0;
	func->eargv[argc] = 0;
	return (ret);
}
