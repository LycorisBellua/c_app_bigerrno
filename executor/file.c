#include "bigerrno.h"

static int	open_infile(t_pl *pl, size_t i, int catch_err);
static int	open_outfile(t_pl *pl, size_t i, int catch_err);
static int	check_file(t_pl *pl, char *file, int mode, int catch_err);

/*
	TODO
	----------------------------------------------------------------------------

	- Is `check_file` useful? Can't we just open the file and see what error 
	comes up?

	SIMPLER HANDLING
	- Initialize fd_src[0] to STDIN_FILENO and fd_src[1] to STDOUT_FILENO, then 
	to the pipes if any, and then tackle the redirections. For a given infile, 
	close fd_src[0] if it wasn't STDIN_FILENO, open the infile, and update 
	fd_src[0] with its fd. Do the same for outfiles.
	- After the redirections, do dup2, and close fd_src[0] and fd_src[1].

	SIGNALS
	- Check the flavor text with a command such as cat. It's a handwritten 
	program which sends a signal to itself. Indeed, there's an issue with 
	SIGQUIT for example. It definitely prints something, and yet my research 
	led me to believe it doesn't.
	- Add flavor text for all signals.
	- Consider handling all signals in the shell itself (external commands are 
	already handled).

	PARSING
	- Add a label to tokens for a simpler parsing. You'd be able to remove the 
	parentheses hack.
*/

int	set_fd_src_from_files(t_pl *pl, int catch_err)
{
	size_t	i;

	pl->fd_src[0] = -1;
	pl->fd_src[1] = -1;
	if (!pl->file || !pl->file[pl->index])
		return (1);
	i = 0;
	while (pl->file[pl->index][i].filename)
	{
		if (pl->file[pl->index][i].io == 0)
		{
			if (!open_infile(pl, i, catch_err))
				return (0);
		}
		else
		{
			if (!open_outfile(pl, i, catch_err))
				return (0);
		}
		++i;
	}
	return (1);
}

static int	open_infile(t_pl *pl, size_t i, int catch_err)
{
	if (pl->fd_src[0] >= 0)
		close(pl->fd_src[0]);
	if (!check_file(pl, pl->file[pl->index][i].filename, R_OK, catch_err))
	{
		pl->fd_src[0] = -1;
		return (0);
	}
	pl->fd_src[0] = open(pl->file[pl->index][i].filename,
			pl->file[pl->index][i].flags);
	return (1);
}

static int	open_outfile(t_pl *pl, size_t i, int catch_err)
{
	if (pl->fd_src[1] >= 0)
		close(pl->fd_src[1]);
	if (!check_file(pl, pl->file[pl->index][i].filename, W_OK, catch_err))
	{
		pl->fd_src[1] = -1;
		return (0);
	}
	errno = 0;
	pl->fd_src[1] = open(pl->file[pl->index][i].filename,
			pl->file[pl->index][i].flags, 0644);
	if (pl->fd_src[1] < 0)
	{
		pl->exit_code = errno;
		pl->err_msg = compose_err_msg(SHELL, 0, pl->file[pl->index][i].filename,
				strerror(pl->exit_code));
		if (pl->exit_code == EISDIR)
			pl->exit_code = EPERM;
		return (0);
	}
	return (1);
}

static int	check_file(t_pl *pl, char *file, int mode, int catch_err)
{
	if (mode == W_OK && access(file, F_OK) < 0)
	{
		errno = 0;
		return (1);
	}
	else if (access(file, mode) < 0)
	{
		if (catch_err)
		{
			pl->exit_code = errno;
			pl->err_msg = compose_err_msg(SHELL, 0, file,
					strerror(pl->exit_code));
			if (pl->exit_code == ENOENT || pl->exit_code == EACCES)
				pl->exit_code = EPERM;
		}
		return (0);
	}
	return (1);
}
