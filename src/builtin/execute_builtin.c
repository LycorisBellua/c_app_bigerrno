#include "bigerrno.h"

static int	execute_original_builtin(t_sh *sh, char **cmdl);

int	execute_builtin(t_sh *sh)
{
	char	**cmdl;

	cmdl = sh->ex->pl.cmdl[sh->ex->pl.index];
	extract_local_update(&cmdl, &sh->local);
	if (!ft_strcmp(cmdl[0], "cd"))
		return (bigerrno_cd(sh, cmdl));
	else if (!ft_strcmp(cmdl[0], "echo"))
		return (bigerrno_echo(cmdl));
	else if (!ft_strcmp(cmdl[0], "exit"))
		return (bigerrno_exit(sh, cmdl));
	else if (!ft_strcmp(cmdl[0], "export"))
		return (bigerrno_export(&sh->env, &sh->hidden, &sh->local, cmdl));
	else if (!ft_strcmp(cmdl[0], "pwd"))
		return (bigerrno_pwd(sh));
	else if (!ft_strcmp(cmdl[0], "set"))
		return (bigerrno_set(sh->hidden, cmdl));
	else if (!ft_strcmp(cmdl[0], "unset"))
		return (bigerrno_unset(sh, cmdl));
	return (execute_original_builtin(sh, cmdl));
}

static int	execute_original_builtin(t_sh *sh, char **cmdl)
{
	if (!ft_strcmp(cmdl[0], "disco"))
		return (bigerrno_disco(sh));
	else if (!ft_strcmp(cmdl[0], "lulu"))
		return (bigerrno_lulu(sh));
	else if (!ft_strcmp(cmdl[0], "matrix"))
		return (bigerrno_matrix(sh, cmdl));
	else if (!ft_strcmp(cmdl[0], "shoot"))
		return (bigerrno_shoot(sh, cmdl));
	return (0);
}
