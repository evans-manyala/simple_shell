#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/**
 * struct data_struct - Structure for the program data
 * @prg: Name of the executable application file.
 * @input: A pointer to the input to be read from the terminal.
 * @cmd_name: Pointer to the  commands typed from the terminal.
 * @exec_iterator: Stores the no. of excecuted
 * command arguments in the terminal.
 * @fd: File descri[tion to the commands entered at the terminal.
 * @uuid: A pointer array to the unique ids of the input
 * @envs: A pointer array to envs used during program execution.
 * @alias: Pointer arrays for aliases.
 */

typedef struct data_struct
{
	char *prg;
	char *input;
	char *cmd_name;
	int exec_iterator;
	int fd;
	char **uuid;
	char **envs;
	char **alias;
};

/**
 * struct in_built - Strucutre for in_built shell arguments to be passed.
 * @in_b: Name for inbuilt arguments.
 * @fn: Function to be called by each inbuilt arguments within the program.
 */
typedef struct in_built
{
	char *in_b;
	int (*fn)(data_struct *d);
};


#endif /* MAIN_H */
