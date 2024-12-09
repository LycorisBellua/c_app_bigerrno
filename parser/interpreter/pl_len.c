#include "parser.h"

size_t	get_pl_len(char **tokens)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 1;
	while (pl_skip_parentheses(tokens, &i))
	{
		if (!ft_strcmp(tokens[i], "|"))
			++len;
		++i;
	}
	return (len);
}
