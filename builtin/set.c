#include "bigerrno.h"

static void	print_in_p_order(t_env **to_print, t_env **not_to_print);

/* TODO: No option required */
int	bigerrno_set(t_env **hidden, char **arg)
{
	if (arg[0] && !arg[1])
	{
		if (hidden && *hidden)
			print_in_p_order(hidden, 0);
	}
	else
	{
		output_error(EPERM, compose_err_msg(SHELL, "set", arg[1],
				strerror(E2BIG)));
		return (EPERM);
	}
	return (0);
}

static void	print_in_p_order(t_env **to_print, t_env **not_to_print)
{
	t_env	*p_order;
	t_env	*smallest;
	t_env	*next_small;
	t_env	*biggest;

	if (!to_print)
		return ;
	p_order = *to_print;
	smallest = find_smallest_p(&p_order);
	biggest = find_biggest_p(&p_order);
	if (!smallest || !biggest || !p_order)
		return ;
	if (smallest && smallest->withvalue && ((!not_to_print || !*not_to_print)
			|| !find_key(not_to_print, smallest->key)))
		printf("%s=%s\n", smallest->key, smallest->value);
	while (smallest != biggest)
	{
		next_small = next_smallest(&p_order, smallest);
		if (next_small && next_small->withvalue
			&& !find_key(not_to_print, next_small->key))
			printf("%s=%s\n", next_small->key, next_small->value);
		smallest = next_small;
	}
	lst_clear(not_to_print);
	return ;
}
