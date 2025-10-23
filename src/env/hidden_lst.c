#include "bigerrno.h"

static void	process_token(t_env **hidden, char *token);
static void	update_value(t_env *node, char *key, char *value, int is_append);

int	only_var(char **arg)
{
	int		i;

	i = 0;
	if (!arg || !*arg)
		return (0);
	while (arg[i])
	{
		if (!ft_strchr(arg[i], '='))
			return (0);
		else if (!valid_keyvalue(arg[i]))
			return (0);
		++i;
	}
	return (1);
}

int	update_hidden(t_env **hidden, char **token)
{
	int	i;

	i = 0;
	if (!token)
		return (0);
	while (token[i])
	{
		process_token(hidden, token[i]);
		++i;
	}
	return (0);
}

int	firstocc(char *s, char c)
{
	int	i;

	i = 0;
	if (!s || !c)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		++i;
	}
	return (-1);
}

static void	process_token(t_env **hidden, char *token)
{
	t_env	*found_node;
	t_env	*node;
	int		first_equal_occurrence;
	int		is_append;
	char	*key_value[2];

	first_equal_occurrence = firstocc(token, '=');
	is_append = token[first_equal_occurrence - 1] == '+';
	key_value[0] = ft_substr(token, 0, first_equal_occurrence - is_append);
	key_value[1] = ft_strdup(token + first_equal_occurrence + 1);
	found_node = find_key(hidden, key_value[0]);
	if (found_node)
		update_value(found_node, key_value[0], key_value[1], is_append);
	else
	{
		node = lst_new(key_value[0], key_value[1]);
		free(key_value[0]);
		free(key_value[1]);
		lstadd_back(hidden, node);
	}
	return ;
}

static void	update_value(t_env *node, char *key, char *value, int is_append)
{
	char	*joined;

	if (is_append && node->value)
	{
		joined = ft_strjoin(node->value, value);
		free(node->value);
		node->value = joined;
		free(key);
		free(value);
	}
	else
	{
		free(node->value);
		node->value = value;
		free(key);
	}
	return ;
}
