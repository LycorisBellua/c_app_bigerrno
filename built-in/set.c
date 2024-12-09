#include "bigerrno.h"

int	bigerrno_hidden(t_env **hidden, char **arg)
{
	if (arg[0] && !arg[1])
	{
		if (!hidden && !*hidden)
			ft_putstr_fd("Nothing_to_print\n", STDERR_FILENO);
		else
			print_in_p_order(hidden, NULL);
	}
	else
	{
		output_error(EPERM, compose_err_msg(SHELL, "hidden", arg[1],
				strerror(E2BIG)));
		return (EPERM);
	}
	return (0);
}
