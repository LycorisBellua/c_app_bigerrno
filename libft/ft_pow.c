#include "libft.h"

long	ft_pow(const int factor, int exponent)
{
	if (exponent == 0)
		return (1);
	return (factor * ft_pow(factor, --exponent));
}
