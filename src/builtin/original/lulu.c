#include "bigerrno.h"

int	bigerrno_lulu(t_sh *sh)
{
	++sh->color;
	if (sh->color >= E_COLOR_LIMIT)
		sh->color = 0;
	set_prompt_color(sh, sh->color);
	set_background_color(sh->color);
	return (0);
}
