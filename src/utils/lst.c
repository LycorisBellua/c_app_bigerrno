#include "bigerrno.h"

static t_env	*lst_last(t_env *last);

t_env	*lst_new(const char *key, const char *value)
{
	t_env	*node;

	if (!key)
		return (0);
	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (0);
	node->key = ft_strdup(key);
	if (value)
		node->value = ft_strdup(value);
	else
		node->value = 0;
	node->withvalue = value != 0;
	node->next = 0;
	node->prev = 0;
	return (node);
}

t_env	*lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return (0);
	tmp = *lst;
	if (!*lst)
	{
		*lst = new;
		return (*lst);
	}
	tmp = lst_last(*lst);
	tmp->next = new;
	new->prev = tmp;
	return (*lst);
}

int	lst_size(t_env **lst)
{
	int		size;
	t_env	*loc;

	size = 0;
	loc = *lst;
	while (loc)
	{
		++size;
		loc = loc->next;
	}
	return (size);
}

void	lst_clear(t_env **lst)
{
	t_env	*current;
	t_env	*next;

	if (!lst || !*lst)
		return ;
	current = *lst;
	while (current)
	{
		next = current->next;
		free(current->key);
		free(current->value);
		free(current);
		current = next;
	}
	*lst = 0;
	return ;
}

static t_env	*lst_last(t_env *last)
{
	if (!last)
		return (0);
	while (last->next)
		last = last->next;
	return (last);
}
