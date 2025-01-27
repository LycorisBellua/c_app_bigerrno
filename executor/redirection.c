#include "bigerrno.h"

static int	update_fd_src_with_files(t_pl *pl);
static void	catch_file_opening_error(t_pl *pl, size_t i);

/*
	TODO
	----------------------------------------------------------------------------

	WILDCARD
	$ echo test*
	test.c test*
	$ rm test*
	rm: cannot remove 'test*': No such file or directory
	-> It should be `test test.c` and then work for both in the second command

	SIGNALS
	- Consider handling all signals in the shell itself (external commands are 
	already handled).

	PARSING
	- Add a label to tokens for a simpler parsing. You'd be able to remove the 
	parentheses hack.
*/

int	redirect_io(t_pl *pl)
{
	pl->fd_std[0] = dup(STDIN_FILENO);
	pl->fd_std[1] = dup(STDOUT_FILENO);
	pl->fd_src[0] = STDIN_FILENO;
	pl->fd_src[1] = STDOUT_FILENO;
	if (pl->index > 0)
		pl->fd_src[0] = pl->fd_pipe[pl->index - 1][0];
	if (pl->index < pl->len - 1)
		pl->fd_src[1] = pl->fd_pipe[pl->index][1];
	else if (pl->index == pl->len - 1 && pl->circular)
		pl->fd_src[1] = pl->fd_circ[1];
	if (!update_fd_src_with_files(pl))
		return (0);
	if (pl->fd_src[0] != STDIN_FILENO)
	{
		dup2(pl->fd_src[0], STDIN_FILENO);
		close(pl->fd_src[0]);
		pl->fd_src[0] = -1;
	}
	if (pl->fd_src[1] != STDOUT_FILENO)
	{
		dup2(pl->fd_src[1], STDOUT_FILENO);
		close(pl->fd_src[1]);
		pl->fd_src[1] = -1;
	}
	return (1);
}

int	restore_io(t_pl *pl)
{
	char	buffer[1024];

	if (!isatty(STDIN_FILENO))
	{
		while (read(STDIN_FILENO, buffer, 1024 - 1) > 0)
			;
	}
	if (pl->fd_src[0] >= 0)
		close(pl->fd_src[0]);
	if (pl->fd_src[1] >= 0)
		close(pl->fd_src[1]);
	if (pl->circular)
	{
		close(pl->fd_circ[0]);
		close(pl->fd_circ[1]);
	}
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	dup2(pl->fd_std[0], STDIN_FILENO);
	close(pl->fd_std[0]);
	dup2(pl->fd_std[1], STDOUT_FILENO);
	close(pl->fd_std[1]);
	output_error(pl->exit_code, pl->err_msg);
	return (pl->exit_code);
}

static int	update_fd_src_with_files(t_pl *pl)
{
	size_t	i;
	int		io;

	if (!pl->file || !pl->file[pl->index])
		return (1);
	i = 0;
	while (pl->file[pl->index][i].filename)
	{
		io = pl->file[pl->index][i].io;
		if (pl->fd_src[io] > STDERR_FILENO)
			close(pl->fd_src[io]);
		pl->fd_src[io] = open(pl->file[pl->index][i].filename,
				pl->file[pl->index][i].flags, 0644);
		if (pl->fd_src[io] < 0)
		{
			catch_file_opening_error(pl, i);
			return (0);
		}
		++i;
	}
	return (1);
}

static void	catch_file_opening_error(t_pl *pl, size_t i)
{
	pl->exit_code = errno;
	pl->err_msg = compose_err_msg(SHELL, 0, pl->file[pl->index][i].filename,
			strerror(pl->exit_code));
	if (pl->exit_code == ENOENT || pl->exit_code == EACCES
		|| pl->exit_code == EISDIR)
		pl->exit_code = EPERM;
	return ;
}
