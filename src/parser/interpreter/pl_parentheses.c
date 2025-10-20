#include "parser.h"

char	*pl_skip_parentheses(char **tokens, size_t *i)
{
	size_t	parentheses;

	parentheses = 0;
	while (tokens[*i])
	{
		if (!ft_strcmp(tokens[*i], "("))
			++parentheses;
		else if (!ft_strcmp(tokens[*i], ")"))
			--parentheses;
		else if (!parentheses)
			break ;
		++*i;
	}
	return (tokens[*i]);
}
