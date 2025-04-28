#include "bigerrno.h"

static void	fork_subprocesses(t_sh *sh, int *pid);
static void	err_fork_loop(t_sh *sh, int fd_pipe[2], char *function);
static int	parent_handles_pipe(t_sh *sh, int fd_pipe[2], int fd_input);

int	execute_pipeline(t_sh *sh)
{
	int	*pid;

	pid = ft_calloc(sh->ex->pl.len + 1, sizeof(int));
	if (!pid)
	{
		sh->ex->pl.exit_code = ENOMEM;
		if (sh->ex->pl.circular)
			close(sh->ex->pl.fd_circ[1]);
		return (sh->ex->pl.exit_code);
	}
	fork_subprocesses(sh, pid);
	if (sh->ex->pl.circular)
		close(sh->ex->pl.fd_circ[1]);
	wait_for_subprocesses(sh, pid, 0);
	free(pid);
	return (sh->ex->pl.exit_code);
}

static void	fork_subprocesses(t_sh *sh, int *pid)
{
	int	fd_input;
	int	fd_pipe[2];

	fd_input = dup(STDIN_FILENO);
	while (sh->ex->pl.index < sh->ex->pl.len)
	{
		if (sh->ex->pl.index < sh->ex->pl.len - 1 && pipe(fd_pipe) < 0)
		{
			err_fork_loop(sh, fd_pipe, "pipe");
			break ;
		}
		pid[sh->ex->pl.index] = fork();
		if (pid[sh->ex->pl.index] < 0)
		{
			err_fork_loop(sh, fd_pipe, "fork");
			break ;
		}
		else if (!pid[sh->ex->pl.index])
			execute_subprocess(sh, fd_pipe, fd_input, pid);
		fd_input = parent_handles_pipe(sh, fd_pipe, fd_input);
		++sh->ex->pl.index;
	}
	close(fd_input);
	return ;
}

static void	err_fork_loop(t_sh *sh, int fd_pipe[2], char *function)
{
	if (!ft_strcmp(function, "fork"))
	{
		close(fd_pipe[0]);
		close(fd_pipe[1]);
	}
	sh->ex->pl.exit_code = errno;
	sh->ex->pl.err_msg = compose_err_msg(0, function, 0,
			strerror(sh->ex->pl.exit_code));
	return ;
}

static int	parent_handles_pipe(t_sh *sh, int fd_pipe[2], int fd_input)
{
	if (sh->ex->pl.index < sh->ex->pl.len - 1)
	{
		close(fd_input);
		fd_input = fd_pipe[0];
		close(fd_pipe[1]);
	}
	return (fd_input);
}
