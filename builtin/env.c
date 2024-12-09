#include "bigerrno.h"

int	bigerrno_env(t_env **env, t_env **hidden, t_env **local, char **arg)
{
	update_env(env, hidden);
	if (!arg[1])
	{
		print_in_p_order(local, 0);
		print_in_p_order(env, local);
	}
	else if (arg[1])
	{
		output_error(EPERM, compose_err_msg(SHELL, "env", arg[1],
				strerror(E2BIG)));
		return (EPERM);
	}
	return (0);
}

/*
	if (DBUG)
		printf("p=%p\t%s=%s\n", node, node->key, node->value);
*/
void	print_in_p_order(t_env **to_print, t_env **not_to_print)
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

t_env	*next_smallest(t_env **p_order, t_env *smallest)
{
	t_env	*next_small;
	t_env	*tmp;

	tmp = *p_order;
	next_small = 0;
	if (!p_order)
		return (0);
	if (!smallest)
		return (0);
	while (tmp)
	{
		if (tmp > smallest && (!next_small || tmp < next_small))
			next_small = tmp;
		tmp = tmp->next;
	}
	return (next_small);
}

t_env	*find_biggest_p(t_env **p_order)
{
	t_env	*tmp;
	t_env	*biggest;

	tmp = *p_order;
	biggest = *p_order;
	while (tmp)
	{
		if (biggest < tmp)
			biggest = tmp;
		tmp = tmp->next;
	}
	return (biggest);
}

t_env	*find_smallest_p(t_env **p_order)
{
	t_env	*tmp;
	t_env	*smallest;

	tmp = *p_order;
	smallest = *p_order;
	while (tmp)
	{
		if (smallest > tmp)
			smallest = tmp;
		tmp = tmp->next;
	}
	return (smallest);
}
