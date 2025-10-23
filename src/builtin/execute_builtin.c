#include "bigerrno.h"

static int	execute_original_builtin(t_sh *sh, char **cmdl);

int	execute_builtin(t_sh *sh)
{
	char	**cmdl;

	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	extract_local_update(&cmdl, &sh->local);
	if (!ft_strcmp(cmdl[0], "cd"))
		return (builtin_cd(sh, cmdl));
	else if (!ft_strcmp(cmdl[0], "echo"))
		return (builtin_echo(cmdl));
	else if (!ft_strcmp(cmdl[0], "exit"))
		return (builtin_exit(sh, cmdl));
	else if (!ft_strcmp(cmdl[0], "export"))
		return (builtin_export(&sh->env, &sh->hidden, &sh->local, cmdl));
	else if (!ft_strcmp(cmdl[0], "pwd"))
		return (builtin_pwd(sh));
	else if (!ft_strcmp(cmdl[0], "set"))
		return (builtin_set(sh->hidden, cmdl));
	else if (!ft_strcmp(cmdl[0], "unset"))
		return (builtin_unset(sh, cmdl));
	return (execute_original_builtin(sh, cmdl));
}

static int	execute_original_builtin(t_sh *sh, char **cmdl)
{
	if (!ft_strcmp(cmdl[0], "disco"))
		return (builtin_disco(sh));
	else if (!ft_strcmp(cmdl[0], "lulu"))
		return (builtin_lulu(sh));
	else if (!ft_strcmp(cmdl[0], "matrix"))
		return (builtin_matrix(sh, cmdl));
	else if (!ft_strcmp(cmdl[0], "shoot"))
		return (builtin_shoot(sh, cmdl));
	return (0);
}
