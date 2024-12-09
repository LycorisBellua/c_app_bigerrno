#include "bigerrno.h"

static int	skip_var(char **cmd);

int	isbuiltin(char **cmd)
{
	char	**cmd_arr;
	int		state;
	int		i;
	int		j;

	if (!cmd[0])
		return (0);
	j = skip_var(cmd);
	cmd_arr = ft_split("cd:echo:exit:export:pwd:set:unset:"
			"lulu:shoot:disco:matrix", ':');
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

int	execute_builtin(t_sh *sh)
{
	char	**cmdl;
	int		code_err;

	code_err = 0;
	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	extract_local_update(&cmdl, &sh->local);
	if (!ft_strcmp(cmdl[0], "cd"))
		code_err = bigerrno_cd(sh, cmdl);
	else if (!ft_strcmp(cmdl[0], "echo"))
		code_err = bigerrno_echo(cmdl);
	else if (!ft_strcmp(cmdl[0], "exit"))
		code_err = bigerrno_exit(sh, cmdl);
	else if (!ft_strcmp(cmdl[0], "export"))
		code_err = bigerrno_export(&sh->env, &sh->hidden, &sh->local, cmdl);
	else if (!ft_strcmp(cmdl[0], "pwd"))
		code_err = bigerrno_pwd(sh);
	else if (!ft_strcmp(cmdl[0], "set"))
		code_err = bigerrno_set(&sh->hidden, cmdl);
	else if (!ft_strcmp(cmdl[0], "unset"))
		code_err = bigerrno_unset(sh, cmdl);
	else
		bigerrno_bonus(sh, cmdl, &code_err);
	return (code_err);
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
