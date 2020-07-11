
#include <ctype.h>
#include <string.h>
#include "strutils.h"

/*
Note: This function returns a pointer to a substring of the original string.
If the given string was allocated dynamically, the caller must not overwrite
that pointer with the returned value, since the original pointer must be
deallocated using the same allocator with which it was allocated.  The return
value must NOT be deallocated using free() etc.
*/

char* trimwhitespace(char* str)
{
	char* end;

	/* Trim leading space */
	while (isspace((unsigned char)*str)) str++;

	if (*str == 0)
		return str;

	/* Trim trailing space */
	end = str + strlen(str) - 1;
	while (end > str && isspace((unsigned char)*end)) end--;

	/* Write new null terminator character */
	end[1] = '\0';

	return str;
}




