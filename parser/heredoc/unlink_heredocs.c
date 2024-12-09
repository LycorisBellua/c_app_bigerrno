#include "parser.h"

void	unlink_heredocs(t_sh *sh)
{
	size_t	i;

	if (!sh->rl.hd)
		return ;
	i = 0;
	while (sh->rl.hd[i])
	{
		unlink(sh->rl.hd[i]);
		++i;
	}
	return ;
}
