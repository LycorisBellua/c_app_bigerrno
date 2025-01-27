#include "parser.h"

char	*compose_heredoc_name(void)
{
	static int	index;
	char		*tmp1;
	char		*tmp2;

	index = (index + 1) % INT_MAX;
	tmp1 = ft_itoa(index);
	tmp2 = ft_strjoin(".heredoc", tmp1);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, ".tmp");
	free(tmp2);
	if (!access(tmp1, F_OK))
		unlink(tmp1);
	return (tmp1);
}
