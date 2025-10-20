#include "bigerrno.h"

int	bigerrno_disco(t_sh *sh)
{
	int	pid[2];

	if (sh->pid_disco)
		kill(sh->pid_disco, SIGKILL);
	sh->pid_disco = fork();
	pid[0] = sh->pid_disco;
	pid[1] = 0;
	if (!sh->pid_disco)
	{
		while ("DISCO YAY" && !g_signum)
			bigerrno_lulu(sh);
		destroy_all_ex(sh);
		free_shell(sh);
		exit(418);
	}
	wait_for_subprocesses(sh, pid, WNOHANG);
	return (sh->ex->pl.exit_code);
}
