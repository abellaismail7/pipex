#include <stdlib.h>
#include "ft_error.h"


void	die(char *basename, char *file)
{
	show_errno(basename, file);
	exit(1);
}

