#include "bigerrno.h"

static int	skip_var(char **cmd);

int	is_builtin(char **cmd)
{
	char	**cmd_arr;
	int		state;
	int		i;
	int		j;

	if (!cmd[0])
		return (0);
	cmd_arr = ft_split("cd:echo:exit:export:pwd:set:unset:"
			"disco:lulu:matrix:shoot", ':');
	j = skip_var(cmd);
	state = 0;
	i = 0;
	while (cmd[j] && cmd_arr[i])
	{
		if (!ft_strcmp(cmd[j], cmd_arr[i]))
		{
			state = 1;
			break ;
		}
		++i;
	}
	free_entire_array((void **)cmd_arr, free);
	return (state);
}

static int	skip_var(char **cmd)
{
	int	j;

	j = 0;
	if (!cmd)
		return (0);
	while (cmd[j])
	{
		if (!ft_strchr(cmd[j], '=') || !valid_keyvalue(cmd[j]))
			break ;
		++j;
	}
	return (j);
}
