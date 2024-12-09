#include "libft.h"

int	ft_strcasecmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (s1[i] && ft_toupper(s1[i]) == ft_toupper(s2[i]))
		++i;
	return ((unsigned char)ft_toupper(s1[i])
		- (unsigned char)ft_toupper(s2[i]));
}
