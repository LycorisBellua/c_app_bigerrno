#include "bigerrno.h"

static t_env	*lst_dup(t_env *src);
static void		manage_env(t_env **hidden, t_env *env_var, t_env *current,
					char **append_value);

int	valid_keyvalue(char *key_value)
{
	int	i;
	int	separator;

	i = 0;
	separator = firstocc(key_value, '=');
	if (key_value[0] == '_' && (!key_value[1] || separator == 1))
		return (0);
	else if (ft_isdigit(key_value[0]))
		return (0);
	else if (ft_isalpha(key_value[i]) || key_value[i] == '_')
	{
		while (key_value[i] && (separator < 0 || i < separator - !!i))
		{
			if (!(ft_isalnum(key_value[i]) || key_value[i] == '_'))
				return (0);
			++i;
		}
		if (ft_isalnum(key_value[i])
			|| key_value[i] == '_' || key_value[i] == '+')
			return (!(separator < 0 && key_value[i] == '+'));
	}
	else
		return (0);
	return (1);
}

t_env	*alpha_order_lst(t_env **env)
{
	t_env	*start;
	t_env	*ordered;
	int		swapped;

	if (!*env)
		return (0);
	start = lst_dup(*env);
	if (!start)
		return (0);
	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		ordered = start;
		while (ordered->next)
		{
			if (ft_strcmp(ordered->key, ordered->next->key) > 0)
			{
				swap_node_content(ordered, ordered->next);
				swapped = 1;
			}
			ordered = ordered->next;
		}
	}
	return (start);
}

void	update_env(t_env **env, t_env **hidden)
{
	t_env	*current;
	t_env	*next;
	t_env	*env_var;
	char	*append_value;

	if (!hidden || !*hidden)
		return ;
	current = *hidden;
	append_value = 0;
	while (current)
	{
		next = current->next;
		env_var = find_key(env, current->key);
		if (env_var && ft_strcmp(current->key, "_") != 0)
			manage_env(hidden, env_var, current, &append_value);
		current = next;
	}
	return ;
}

static t_env	*lst_dup(t_env *src)
{
	t_env	*to_copy;
	t_env	*dup;
	t_env	*node;
	int		len;
	int		i;

	to_copy = src;
	dup = 0;
	len = lst_size(&src);
	i = 0;
	while (to_copy && i < len)
	{
		node = add_node(&dup, to_copy->key, to_copy->value);
		if (!node)
		{
			lst_clear(&dup);
			return (0);
		}
		to_copy = to_copy->next;
		++i;
	}
	return (dup);
}

static void	manage_env(t_env **hidden, t_env *env_var, t_env *current,
	char **append_value)
{
	if (env_var->key[ft_strlen(env_var->key) - 1] == '+')
		*append_value = ft_strjoin(env_var->value, current->value);
	if (env_var->value)
	{
		free(env_var->value);
		env_var->value = 0;
	}
	if (*append_value)
		env_var->value = *append_value;
	else
		env_var->value = ft_strdup(current->value);
	env_var->withvalue = 1;
	if (current == *hidden)
		*hidden = current->next;
	clear_node(current);
}
