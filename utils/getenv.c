#include "bigerrno.h"

t_env	*find_key(t_env **lst, char *key)
{
	t_env	*tmp;

	if (!key || !lst || !*lst)
		return (0);
	tmp = *lst;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
			return (tmp);
		tmp = tmp->next;
	}
	return (0);
}

char	*extract_key(int separator, char *key_value)
{
	if (separator > 0 && key_value[separator - 1] == '+')
		return (ft_substr(key_value, 0, separator - 1));
	else if (separator > 0)
		return (ft_substr(key_value, 0, separator));
	return (ft_strdup(key_value));
}

char	*get_var_value(t_sh *sh, char *key)
{
	t_env	*var;

	var = 0;
	if (sh->hidden)
		var = find_key(&sh->hidden, key);
	if (!var && sh->env)
		var = find_key(&sh->env, key);
	if (var)
		return (var->value);
	return (0);
}
