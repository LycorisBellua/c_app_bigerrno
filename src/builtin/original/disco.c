#include "bigerrno.h"

/*
	Only the parent process can start disco, but any process can stop it. The 
	reason a child process cannot start it, is that it might be tricky for a 
	child process to communicate the disco PID to the parent.

	That might be something we can figure out with the background jobs feature.
*/
int	bigerrno_disco(t_sh *sh)
{
	if (bigerrno_disco_stop(sh) || sh->ex->pl.len > 1)
		return (sh->ex->pl.exit_code);
	sh->pid_disco = fork();
	if (!sh->pid_disco)
	{
		if (set_signal_handling(SIGINT, signal_handler))
		{
			while ("DISCO YAY" && !g_signum)
			{
				bigerrno_lulu(sh);
				set_background_color(sh->color_scheme);
			}
		}
		destroy_all_ex(sh);
		free_shell(sh);
		exit(418);
	}
	return (sh->ex->pl.exit_code);
}

int	bigerrno_disco_stop(t_sh *sh)
{
	int	was_running;

	was_running = 0;
	if (sh->pid_disco)
	{
		was_running = 1;
		if (sh->ex && sh->ex->pl.len > 1)
			kill(sh->pid_disco, SIGINT);
		else
		{
			if (!waitpid(sh->pid_disco, 0, WNOHANG))
				kill(sh->pid_disco, SIGINT);
			else
				was_running = 0;
			if (was_running)
			{
				while (waitpid(sh->pid_disco, 0, 0) < 0)
					;
			}
		}
	}
	sh->pid_disco = 0;
	return (was_running);
}
