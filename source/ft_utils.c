#include "fdf.h"

void	ft_error(char *str)
{
	ft_putendl_fd(str, 2);
	exit(EXIT_FAILURE);
}

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int	count_array(char **array)
{
	int ret;

	ret = -1;
	while (array[++ret])
		;
	return (ret);
}