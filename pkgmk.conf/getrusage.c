#include <builtins.h>
#include <shell.h>
#include <stdio.h>

/*
	enable -f ....../getrusage.so getrusage
	getrusage
	echo "$REPLY KB"
*/

static int mygetrusage(WORD_LIST *list)
{
	struct rusage ru;
	char ru_str[100];

	getrusage(RUSAGE_CHILDREN, &ru);

	snprintf(ru_str, sizeof(ru_str), "%li", ru.ru_maxrss);
	setenv("REPLY", ru_str, 1);

	return EXECUTION_SUCCESS;
}

struct builtin getrusage_struct = {
	"getrusage",		// builtin command name
	mygetrusage,		// function called when issueing this command
	BUILTIN_ENABLED,	// initial flag
	NULL,			// long description
	"getrusage",		// short description
	0,
};
