#include "bigerrno.h"

/*
	The subprocess either exited normally (`exit` or returning from `main`) or 
	due to a signal. Exit codes are in a [0-255] range, with the [0-127] range 
	meant for normal exits, and the [128-255] range for signaled exits. Only a 
	normal exit provides an exit code, which is why 128 is added to a signal 
	number to create the exit code.

	The macros in `wait_for_subprocesses` are part of `waitpid` and are not 
	extra functions.

	About the core dump, it should be generated on SIGQUIT, but I'm not certain 
	it happens and print the flavor text anyway.
*/

void	wait_for_subprocesses(t_sh *sh, int *pid, int options)
{
	size_t	i;
	int		status;
	int		signum;

	i = 0;
	status = 0;
	while (pid[i])
	{
		while (waitpid(pid[i], &status, options) < 0 && errno == EINTR)
			errno = 0;
		++i;
	}
	if (sh->ex->pl.exit_code || !status)
		return ;
	else if (WIFEXITED(status))
		sh->ex->pl.exit_code = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signum = WTERMSIG(status);
		sh->ex->pl.exit_code = 128 + signum;
		ft_putstr_fd(get_sig_flavor_text(signum), STDERR_FILENO);
	}
	return ;
}
