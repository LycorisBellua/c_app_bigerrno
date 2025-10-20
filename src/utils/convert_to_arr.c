#include "bigerrno.h"

char	**convert_to_arr(t_env *env)
{
	char	**env_arr;
	char	*tmp;
	int		size;
	int		i;

	if (!env)
		return (0);
	size = lst_size(&env);
	env_arr = ft_calloc(size + 1, sizeof(char *));
	i = 0;
	while (env)
	{
		tmp = ft_strjoin(env->key, "=");
		env_arr[i++] = ft_strjoin(tmp, env->value);
		free(tmp);
		env = env->next;
	}
	return (env_arr);
}
