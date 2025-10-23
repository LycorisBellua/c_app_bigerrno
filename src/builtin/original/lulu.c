#include "bigerrno.h"

int	builtin_lulu(t_sh *sh)
{
	++sh->color_scheme;
	if (sh->color_scheme >= E_COLOR_LIMIT)
		sh->color_scheme = 0;
	return (0);
}
