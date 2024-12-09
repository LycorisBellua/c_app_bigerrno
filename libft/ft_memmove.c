#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	const char	*s;

	if (!dest && !src)
		return (dest);
	else if (!n)
		return (dest);
	else if (dest == src)
		return (dest);
	else if (dest < src)
		return (ft_memcpy(dest, src, n));
	i = n - 1;
	d = dest;
	s = src;
	while (i > 0)
	{
		d[i] = s[i];
		--i;
	}
	d[i] = s[i];
	return (dest);
}
