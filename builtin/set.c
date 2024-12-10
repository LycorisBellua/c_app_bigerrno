#include "bigerrno.h"

/* No option required */
int	bigerrno_set(t_env *hidden, char **arg)
{
	t_env	*sorted;
	t_env	*tmp;

	if (!hidden || get_array_length((void **)arg) > 1)
		return (0);
	sorted = alpha_order_lst(&hidden);
	tmp = sorted;
	while (tmp)
	{
		printf("%s=", tmp->key);
		if (tmp->value)
			printf("%s", tmp->value);
		printf("\n");
		tmp = tmp->next;
	}
	lst_clear(&sorted);
	return (0);
}
