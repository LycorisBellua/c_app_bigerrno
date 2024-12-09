#include "bigerrno.h"

void	bigerrno_bonus(t_sh *sh, char **cmdl, int *code_err)
{
	if (!ft_strcmp(cmdl[0], "lulu"))
		*code_err = bigerrno_lulu(sh, &sh->color);
	else if (!ft_strcmp(cmdl[0], "disco"))
		*code_err = bigerrno_disco(sh, &sh->color);
	else if (!ft_strcmp(cmdl[0], "shoot"))
		*code_err = bigerrno_shoot(sh, &sh->color, cmdl);
	else if (!ft_strcmp(cmdl[0], "matrix"))
		*code_err = bigerrno_matrix(sh, cmdl);
	return ;
}
