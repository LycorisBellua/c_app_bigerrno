#include "libft.h"

int	ft_strncasecmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!n)
		return (0);
	i = 0;
	while (i < n - 1 && s1[i] && ft_toupper(s1[i]) == ft_toupper(s2[i]))
		++i;
	return ((unsigned char)ft_toupper(s1[i])
		- (unsigned char)ft_toupper(s2[i]));
}
