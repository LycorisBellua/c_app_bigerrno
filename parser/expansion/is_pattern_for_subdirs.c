#include "parser.h"

int	is_pattern_for_subdirs(const char *pattern)
{
	char	*p_slash;

	if (!pattern)
		return (0);
	p_slash = ft_strchr(pattern, '/');
	if (!p_slash)
		return (0);
	while (*++p_slash == '/')
		;
	return (*p_slash);
}
