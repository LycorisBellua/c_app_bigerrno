#include "parser.h"

char	*concatenate_all_cmdl_lines(t_sh *sh)
{
	size_t	i;
	char	*tmp;
	char	*cmdl;

	if (!sh->rl.arr)
		return (0);
	cmdl = ft_strdup(sh->rl.arr[0]->value);
	if (!cmdl)
		return (0);
	i = 1;
	while (sh->rl.arr[i])
	{
		if (!sh->rl.arr[i]->is_heredoc)
		{
			tmp = ft_strjoin(cmdl, sh->rl.arr[i]->value);
			if (!tmp)
				return (cmdl);
			free(cmdl);
			cmdl = tmp;
		}
		++i;
	}
	return (cmdl);
}
