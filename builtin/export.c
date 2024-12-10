#include "bigerrno.h"

static void	print_export_lst(t_env **lst);
static void	add_or_update_var(t_env **env, char *key_value);
static void	update_var(t_env *var, char *key_value, int separator);
static void	switch_key_to_localvar(char **onlykey, t_env **local);

int	bigerrno_export(t_env **env, t_env **hidden, t_env **local, char **arg)
{
	t_env	*sorted;
	int		n;

	update_env(env, hidden);
	if (get_array_length((void **)arg) == 1)
	{
		sorted = alpha_order_lst(env);
		print_export_lst(&sorted);
		lst_clear(&sorted);
	}
	else
	{
		n = 0;
		while (arg[++n])
		{
			switch_key_to_localvar(&arg[n], local);
			if (valid_keyvalue(arg[n]))
				add_or_update_var(env, arg[n]);
			else
				output_error(EPERM,
					compose_err_msg(SHELL, "export", arg[n], ERR_EXPORT));
		}
		lst_clear(local);
	}
	return (0);
}

static void	print_export_lst(t_env **lst)
{
	t_env	*tmp;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		if (tmp->withvalue)
			printf("%s %s=\"%s\"\n", MSG_EXPORT, tmp->key, tmp->value);
		else
			printf("%s %s\n", MSG_EXPORT, tmp->key);
		tmp = tmp->next;
	}
	return ;
}

static void	switch_key_to_localvar(char **onlykey, t_env **local)
{
	t_env	*tmp;
	char	*compose;

	tmp = *local;
	if (!local || !*local || !onlykey || !*onlykey)
		return ;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, *onlykey))
		{
			free(*onlykey);
			compose = ft_strjoin(tmp->key, "=");
			*onlykey = ft_strjoin(compose, tmp->value);
			free(compose);
		}
		tmp = tmp->next;
	}
	return ;
}

static void	add_or_update_var(t_env **env, char *key_value)
{
	t_env	*var;
	char	*key;
	char	*value;
	int		separator;

	separator = firstocc(key_value, '=');
	key = extract_key(separator, key_value);
	var = find_key(env, key);
	if (var)
	{
		if (var->withvalue)
			update_var(var, key_value, separator);
	}
	else if (separator > 0)
	{
		value = get_literal_token(key_value + separator + 1);
		add_node(env, key, value);
		free(value);
	}
	else
		add_node(env, key_value, 0);
	free(key);
	return ;
}

static void	update_var(t_env *var, char *key_value, int separator)
{
	char	*tmp_value;
	char	*tmp_newvalue;

	if (separator > 0 && key_value[separator - 1] == '+')
	{
		tmp_newvalue = get_literal_token(key_value + separator + 1);
		tmp_value = ft_strjoin(var->value, tmp_newvalue);
		free(var->value);
		free(tmp_newvalue);
		var->value = tmp_value;
		var->withvalue = 1;
	}
	else if (separator > 0)
	{
		free(var->value);
		var->value = get_literal_token(key_value + separator + 1);
		var->withvalue = 1;
	}
	return ;
}
