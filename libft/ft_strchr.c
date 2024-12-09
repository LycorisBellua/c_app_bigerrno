#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;

	if (!c)
		return ((char *)s + ft_strlen(s));
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return ((char *)s + i);
		++i;
	}
	return (0);
}
