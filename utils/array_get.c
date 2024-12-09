#include "bigerrno.h"

size_t	get_array_length(void **array)
{
	size_t	i;

	if (!array)
		return (0);
	i = 0;
	while (array[i])
		++i;
	return (i);
}

size_t	find_array_index(void **array, int (*condition)(void *element))
{
	size_t	i;

	if (!array || !condition)
		return (0);
	i = 0;
	while (array[i])
	{
		if (condition(array[i]))
			return (i);
		++i;
	}
	return (i);
}
