#include "bigerrno.h"

static void	insert_string(char ***arr, char *s, size_t i);
static char	*concatenate_strings(char **arr, const char *separator);

int	output_error(int code, char *msg)
{
	if (code)
	{
		ft_putstr_fd(msg, STDERR_FILENO);
		free(msg);
	}
	return (code);
}

char	*compose_err_msg(const char *shell, const char *cmd, const char *arg,
			const char *msg)
{
	size_t	i;
	char	*str;
	char	**arr;

	i = 0;
	str = 0;
	arr = 0;
	while (i < 4)
	{
		if (i == 0)
			insert_string(&arr, ft_strjoin(shell, ": "), i);
		else if (i == 1)
			insert_string(&arr, ft_strjoin(cmd, ": "), i);
		else if (i == 2)
			insert_string(&arr, ft_strjoin(arg, ": "), i);
		else
			insert_string(&arr, ft_strjoin(msg, "\n"), i);
		++i;
	}
	str = concatenate_strings(arr, 0);
	free_entire_array((void **)arr, free);
	return (str);
}

static void	insert_string(char ***arr, char *s, size_t i)
{
	if (s)
		insert_array_element((void ***)arr, (void *)s, i);
	return ;
}

static char	*concatenate_strings(char **arr, const char *separator)
{
	size_t	i;
	char	*joined;
	char	*tmp;

	if (!arr || !arr[0])
		return (0);
	joined = ft_strdup(arr[0]);
	i = 1;
	while (arr[i])
	{
		if (!separator)
			tmp = joined;
		else
		{
			tmp = ft_strjoin(joined, separator);
			free(joined);
		}
		joined = ft_strjoin(tmp, arr[i]);
		free(tmp);
		++i;
	}
	return (joined);
}
