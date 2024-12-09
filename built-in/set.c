#include "bigerrno.h"

/* TODO: No option required */
int	bigerrno_set(t_env **hidden, char **arg)
{
	if (arg[0] && !arg[1])
	{
		if (hidden && *hidden)
			print_in_p_order(hidden, NULL);
	}
	else
	{
		output_error(EPERM, compose_err_msg(SHELL, "set", arg[1],
				strerror(E2BIG)));
		return (EPERM);
	}
	return (0);
}
